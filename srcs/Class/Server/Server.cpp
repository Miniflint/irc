#include "Server.hpp"
#include <algorithm>
#include <map>

Server::Server(uint16_t port, std::string password) : _port(port), _password(password), _host(std::string(SERV_HOST_NAME))
{
	this->_clients.assign(MAX_SOCKET_FD, NULL);
	const std::string t[] = {
		"ADMIN", "AWAY", "CAP", "CNOTICE", "CPRIVMSG", "CONNECT", "DIE", "ERROR",
		"HELP", "INFO", "INVITE", "ISON", "JOIN", "KICK", "KILL", "KNOCK",
		"LINKS","LIST","LUSERS","MODE","MOTD","NAMES","NICK","NOTICE","OPER",
		"PART","PASS","PING","PONG","PRIVMSG","QUIT","QUOTE","REHASH","RULES",
		"SERVER","SQUERY","SQUIT","SETNAME","SILENCE","STATS","SUMMON",
		"TIME","TOPIC","TRACE","USER","USERHOST","USERIP","USERS","VERSION",
		"WALLOPS","WATCH","WHO","WHOIS","WHOWAS", "DCC", ":"
	};
	const Server::cmdFn func_list[] = {
		&Server::handle_admin, &Server::handle_away, &Server::handle_cap, &Server::handle_cnotice,
		&Server::handle_cprivmsg, &Server::handle_connect, &Server::handle_die, &Server::handle_error,
		&Server::handle_help, &Server::handle_info, &Server::handle_invite, &Server::handle_ison,
		&Server::handleJoin, &Server::handle_kick, &Server::handle_kill, &Server::handle_knock,
		&Server::handle_links, &Server::handleList, &Server::handle_lusers, &Server::handleMode,
		&Server::handle_motd, &Server::handle_names, &Server::handleNick, &Server::handle_notice,
		&Server::handle_oper, &Server::handlePart, &Server::handlePass, &Server::handlePing,
		&Server::handle_pong, &Server::handlePrivMsg, &Server::handleQuit, &Server::handle_quote,
		&Server::handle_rehash, &Server::handle_rules, &Server::handle_server, &Server::handle_squery,
		&Server::handle_squit, &Server::handle_setname, &Server::handle_silence, &Server::handle_stats,
		&Server::handle_summon, &Server::handle_time, &Server::handle_topic, &Server::handle_trace,
		&Server::handleUser, &Server::handle_userhost, &Server::handle_userip, &Server::handle_users,
		&Server::handle_version, &Server::handle_wallops, &Server::handle_watch, &Server::handleWho,
		&Server::handle_whois, &Server::handle_whowas, &Server::handleDcc, &Server::handle_message
	};
	for (unsigned int i = 0; i <= END; i++)
		this->_commands.add(t[i], func_list[i]);
	this->_commands.createGraph();
	this->_channelSpecifiers.channelType = "&#";
	this->_channelSpecifiers.channelLen = 32;
	this->_channelSpecifiers.channelAuthPrefix = "(qaohv)~&@%+";
	this->_channelSpecifiers.channelMode = ",,,ismntklb";
	this->_motd.motd = "This is the current message of the day";
	this->_motd.announcements.push_back("Today is the day we are working on channels");
	this->_motd.announcements.push_back("And we hope to be able to live long");
	this->_motd.announcements.push_back("Please Respect the rules !");
	this->_clientSpecifiers.nickLenMax = 12;
}

Server::~Server()
{
	const std::vector<Client *>::const_iterator end = this->_clients.end();
	for (std::vector<Client *>::iterator it = this->_clients.begin(); it != end; it++)
		if (*it) { delete *it; *it = NULL; }
	this->_clients.clear();
}

bool    Server::_validateAccess(Client &c, std::string &command)
{
	// if (command != "PASS" && !(c->flagsLogin & FLAG_CLIENT_PASS))
	// 	return (false);
	// if (command == "USER" && (c->flagsLogin & FLAG_CLIENT_USER))
	// 	return (false);
	if (command == "PASS" || command == "NICK" || command == "USER" || command == "QUIT" || command=="CAP")
		return (true);
	if (c.flagsLogin != FLAG_CLIENT_FULL)
		return (this->handleErrNotregistered(c), this->poolOut.push(c.getFd()), false);
	return (true);
}

bool    Server::_validateCommand(Client &c, cmdFn &func, std::string &command)
{
	try {
		func = this->_commands[command];
	} catch (std::exception &e) {
		return (this->handleErrUnknowncommand(c, command), this->poolOut.push(c.getFd()), false);
	};
	return (true);
}

void	Server::deconnectClient(int fd, std::string error, std::string message) {
	Client	&c = this->getClient(fd);
	if (!error.empty())
	{
		this->sendToClient(c, error);
		c.quitRequest = CLIENT_QUIT_REQUEST;
	}
	if (!c.buffer.empty())
		c.quitRequest = CLIENT_QUIT_REQUEST;
	else
		c.quitRequest = CLIENT_QUIT_ACCEPT;
	this->poolQuit.push_back(fd);
	c.setBufferQuit(message);
}

bool	Server::doCommand(size_t fd) //Est-ce qu'il y a une commande fini
{
	Client *c = this->_clients[fd];
	if (!c)
		return (false);
	while (true)
	{
		if (c->buffer.size() <= 2)
			return (false);
		size_t index = c->buffer.find("\r\n");
		if (index == std::string::npos && c->buffer.length() < MAX_PACKET_SIZE)
			return (false);
		else if (index == std::string::npos && c->buffer.length() >= MAX_PACKET_SIZE) {
			c->setWarning(c->getWarning() + 1);
			serverReceivesLogError(c->buffer, "too long and unfinished");
			c->buffer.clear();
			return (false);
		} else if (index + 2 >= MAX_PACKET_SIZE ) {
			c->setWarning(c->getWarning() + 1);
			serverReceivesLogError(c->buffer.substr(0, index), "too long");
			c->buffer.erase(0, index + 2);
			continue;
		}
		std::string			sanitizedClientBuffer(c->buffer.begin(), (c->buffer.begin() + index));
		c->buffer.erase(0, index + 2);
		std::istringstream	iss(sanitizedClientBuffer);
		std::string			cmd;
		cmdFn				func;
		iss >> cmd;
		// std::cout << sanitizedClientBuffer << std::endl; 
		if (!this->_validateAccess(*c, cmd) || !this->_validateCommand(*c, func, cmd))
		{
			serverReceivesLogError(c->buffer.substr(0, index), "not valid");
			const int warnings = c->getWarning() + 1;
			c->setWarning(warnings);
			// kick user
			if (warnings > 2)
				this->deconnectClient(c->getFd(), "Tu as été kick batard\r\n", "un batard a été kick\r\n");
			std::cout << "You get a warning (" << warnings << ")" << std::endl;
			continue ;
		}
		serverReceivesLog(sanitizedClientBuffer);
		(this->*func)(*c, iss);
	}
}

Client	&Server::getClient(size_t fd)
{
	return (*(this->_clients[fd]));
}

std::string						Server::getIp(void) const
{
	return (this->_host);
}

void							Server::setIp(std::string ip)
{
	this->_host = ip;
}

// std::string		Server::_makeHostMask(Client &c) {
// 	std::string	hostMask(":");
// 	return (hostMask.append(c.getNick()).append(1, '!').append(c.getUserName()).append(1, '@').append(c.getHostName()));
// }

bool	Server::sendToClient(Client &source, std::string message)
{
	source.addBufferOut(message);
	this->poolOut.push(source.getFd());
	return (true);
}

const std::string		&Server::_getPassword()
{
	return (this->_password);
}

void					Server::_sendAllWelcome(Client &c)
{
	this->handleRplWelcome(c);
	this->handleRplYourHost(c);
	this->handleRplCreated(c);
	this->handleRplMyinfo(c);
	this->handleRplISupport(c);
	this->handleRplMotdstart(c);
	this->handleRplMotd(c);
	this->handleRplEndofmotd(c);
	this->addClientToChannel(c, "&general");
	c.serverAccess |= CLIENT_ACCESS_FULL;
	this->poolOut.push(c.getFd());
}
