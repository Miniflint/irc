#include "Server.hpp"
#include <algorithm>
#include <map>

Server::Server(uint16_t port, std::string password) : _port(port), _password(password), _ip(std::string("0.0.0.0"))
{
	this->_clients.assign(MAX_SOCKET_FD, NULL);
	const std::string t[] = {
		"ADMIN", "AWAY", "CNOTICE", "CPRIVMSG", "CONNECT", "DIE", "ERROR",
		"HELP", "INFO", "INVITE", "ISON", "JOIN", "KICK", "KILL", "KNOCK",
		"LINKS","LIST","LUSERS","MODE","MOTD","NAMES","NICK","NOTICE","OPER",
		"PART","PASS","PING","PONG","PRIVMSG","QUIT","QUOTE","REHASH","RULES",
		"SERVER","SQUERY","SQUIT","SETNAME","SILENCE","STATS","SUMMON",
		"TIME","TOPIC","TRACE","USER","USERHOST","USERIP","USERS","VERSION",
		"WALLOPS","WATCH","WHO","WHOIS","WHOWAS", "DCC", ":"
	};

	const Server::cmdFn func_list[] = {
		&Server::handle_admin, &Server::handle_away, &Server::handle_cnotice, &Server::handle_cprivmsg,
		&Server::handle_connect, &Server::handle_die, &Server::handle_error, &Server::handle_help,
		&Server::handle_info, &Server::handle_invite, &Server::handle_ison, &Server::handle_join,
		&Server::handle_kick, &Server::handle_kill, &Server::handle_knock, &Server::handle_links,
		&Server::handle_list, &Server::handle_lusers, &Server::handle_mode, &Server::handle_motd,
		&Server::handle_names, &Server::handleNick, &Server::handle_notice, &Server::handle_oper,
		&Server::handle_part, &Server::handle_pass, &Server::handle_ping, &Server::handle_pong,
		&Server::handlePrivMsg, &Server::handleQuit, &Server::handle_quote, &Server::handle_rehash,
		&Server::handle_rules, &Server::handle_server, &Server::handle_squery, &Server::handle_squit,
		&Server::handle_setname, &Server::handle_silence, &Server::handle_stats, &Server::handle_summon,
		&Server::handle_time, &Server::handle_topic, &Server::handle_trace, &Server::handleUser,
		&Server::handle_userhost, &Server::handle_userip, &Server::handle_users, &Server::handle_version,
		&Server::handle_wallops, &Server::handle_watch, &Server::handle_who, &Server::handle_whois,
		&Server::handle_whowas, &Server::handleDcc, &Server::handle_message
	};

	for (unsigned int i = 0; i <= END; i++)
		this->_commands.add(t[i], func_list[i]);
	this->_commands.create_graph();
}

Server::~Server()
{
	const std::vector<Client *>::const_iterator end = this->_clients.end();
	for (std::vector<Client *>::iterator it = this->_clients.begin(); it != end; it++)
		if (*it) { delete *it; *it = NULL; }
	this->_clients.clear();
}

bool    Server::_validateAccess(Client *c, std::string &command)
{
	if (command == "NICK" || command == "USER" || command == "QUIT")
		return (true);
	try {
		const std::string	nick = c->getNick();
		if (c->getUserName().empty() || nick.empty())
			throw std::exception();
		(void)this->_clientTrie[nick];
	} catch (std::exception &e) {
		std::cerr << "[ERROR]: User not authorized" << std::endl;
		c->buffer = "";
		return (false);
	}
	return (true);
}

bool    Server::_validateCommand(cmdFn &func, std::string &command)
{
	try {
		func = this->_commands[command];
	} catch (std::exception &e) {
		std::cerr << "[ERROR]: " << command << " does not exist" << std::endl;
		return (false);
	};
	return (true);
}

bool	Server::doCommand(size_t fd) //Est-ce qu'il y a une commande fini
{
	Client *c = this->_clients[fd];
	if (!c || c->buffer.size() <= 2)
		return (false);
	size_t index = c->buffer.find("\r\n");
	if (index == std::string::npos && c->buffer.length() < MAX_PACKET_SIZE)
		return (false);
	else if (index == std::string::npos && c->buffer.length() >= MAX_PACKET_SIZE) {
		c->setWarning(c->getWarning() + 1);
		c->buffer.clear();
		return (false);
	} else if (index >= MAX_PACKET_SIZE ) {
		c->setWarning(c->getWarning() + 1);
		c->buffer.erase(0, index + 2);
		return (false);
	}
	c->buffer.replace(index, 2, "\n");
	std::string			sanitizedClientBuffer(c->buffer);
	c->buffer.erase(0, index);
	std::istringstream	iss(sanitizedClientBuffer);
	std::string			cmd;
	cmdFn				func;
	std::cout << sanitizedClientBuffer << std::endl;
	iss >> cmd;
	if (!this->_validateCommand(func, cmd) || !this->_validateAccess(c, cmd))
	{
		const int warnings = c->getWarning() + 1;
		c->setWarning(warnings);
		// kick user
		if (warnings > 2)
			this->poolQuit.push(c->getFd());
		std::cout << "You get a warning (" << warnings << ")" << std::endl;
		return (false);
	}
	return ((this->*func)(*c, iss));
}

Client	&Server::getClient(size_t fd)
{
	return (*(this->_clients[fd]));
}

std::string						Server::getIp(void) const
{
	return (this->_ip);
}

void							Server::setIp(std::string ip)
{
	this->_ip = ip;
}

bool	Server::sendToClient(Client &source, std::string message)
{
	source.addBufferOut(message);
	this->poolOut.push(source.getFd());
	return (true);
}

bool	Server::sendRPLToClient(Client &source, std::string message, uint16_t code)
{
	std::map<uint16_t, std::string> t;
	(void)t;
	(void)code;
	source.addBufferOut(message);
	this->poolOut.push(source.getFd());
	return (true);
}