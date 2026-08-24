#include "Server.hpp"
#include <algorithm>
#include <map>

Server::Server(uint16_t port, std::string password) : _port(port), _password(password), _host(std::string(SERV_HOST_NAME)), _serverVersion(std::string(SERV_VERSION)), _adminPass(ADMIN_PASS), _operatorPass(OPERATOR_PASS), _adminName(ADMIN_ID), _operatorName(OPERATOR_ID)
{
	this->_clients.assign(MAX_SOCKET_FD, NULL);
	const std::string t[] = {
		"ADMIN", "AWAY", "CAP", "CNOTICE", "CPRIVMSG", "CONNECT", "DIE", "RESTART", "ERROR",
		"HELP", "INFO", "INVITE", "ISON", "JOIN", "KICK", "KILL", "KNOCK",
		"LINKS","LIST","LUSERS","MODE","MOTD","NAMES","NICK","NOTICE","OPER",
		"PART","PASS","PING","PONG","PRIVMSG","QUIT","QUOTE","REHASH","RULES",
		"SERVER","SQUERY","SQUIT","SETNAME","SILENCE","STATS","SUMMON",
		"TIME","TOPIC","TRACE","USER","USERHOST","USERIP","USERS","VERSION",
		"WALLOPS","WATCH","WHO","WHOIS","WHOWAS", "DCC", ":"
	};
	const Server::cmdFn func_list[] = {
		&Server::handle_admin, &Server::handleAway, &Server::handleCap, &Server::handle_cnotice,
		&Server::handle_cprivmsg, &Server::handle_connect, &Server::handleDie, &Server::handleRestart, &Server::handle_error,
		&Server::handleHelp, &Server::handleInfo, &Server::handleInvite, &Server::handle_ison,
		&Server::handleJoin, &Server::handleKick, &Server::handleKill, &Server::handle_knock,
		&Server::handle_links, &Server::handleList, &Server::handle_lusers, &Server::handleMode,
		&Server::handle_motd, &Server::handleNames, &Server::handleNick, &Server::handle_notice,
		&Server::handleOper, &Server::handlePart, &Server::handlePass, &Server::handlePing,
		&Server::handle_pong, &Server::handlePrivMsg, &Server::handleQuit, &Server::handle_quote,
		&Server::handle_rehash, &Server::handle_rules, &Server::handle_server, &Server::handle_squery,
		&Server::handle_squit, &Server::handle_setname, &Server::handle_silence, &Server::handle_stats,
		&Server::handle_summon, &Server::handle_time, &Server::handleTopic, &Server::handle_trace,
		&Server::handleUser, &Server::handle_userhost, &Server::handle_userip, &Server::handle_users,
		&Server::handle_version, &Server::handle_wallops, &Server::handle_watch, &Server::handleWho,
		&Server::handle_whois, &Server::handle_whowas, &Server::handleDcc, &Server::handle_message
	};
	for (unsigned int i = 0; i <= END; i++)
		this->_commands.add(t[i], func_list[i]);
	this->_commands.createGraph();
	this->_channelSpecifiers.channelType = "#&";
	this->_channelSpecifiers.channelLen = 32;
	this->_channelSpecifiers.channelAuthPrefix = "(qaohv)~&@%+";
	this->_channelSpecifiers.channelMode = "b,k,l,ismnt";
	this->_channelSpecifiers.channelModeChanges = 5;
	this->_motd.motd = "This is the current message of the day";
	this->_motd.announcements.push_back("Today we are working on littles bug fixes");
	this->_motd.announcements.push_back("And we hope to be able to live long happy lifes");
	this->_motd.announcements.push_back("Please Respect the rules !");
	this->_clientSpecifiers.nickLenMax = 12;
	this->_clientSpecifiers.userMode = "ixdRgBoOaA";
	this->_helpTrie.add("AWAY", this->helpAway());
	this->_helpTrie.add("CAP", this->helpCap());
	this->_helpTrie.add("DIE", this->helpDie());
	this->_helpTrie.add("RESTART", this->helpRestart());
	this->_helpTrie.add("INFO", this->helpInfo());
	this->_helpTrie.add("INVITE", this->helpInvite());
	this->_helpTrie.add("JOIN", this->helpJoin());
	this->_helpTrie.add("KICK", this->helpKick());
	this->_helpTrie.add("KILL", this->helpKill());
	this->_helpTrie.add("LIST", this->helpList());
	this->_helpTrie.add("MODE", this->helpMode());
	this->_helpTrie.add("NAMES", this->helpNames());
	this->_helpTrie.add("NICK", this->helpNick());
	this->_helpTrie.add("OPER", this->helpOper());
	this->_helpTrie.add("PART", this->helpPart());
	this->_helpTrie.add("PASS", this->helpPass());
	this->_helpTrie.add("PING", this->helpPing());
	this->_helpTrie.add("PRIVMSG", this->helpPrivmsg());
	this->_helpTrie.add("QUIT", this->helpQuit());
	this->_helpTrie.add("TOPIC", this->helpTopic());
	this->_helpTrie.add("USER", this->helpUser());
	this->_helpTrie.add("WHO", this->helpWho());
}

Server::~Server()
{
	const std::vector<Client *>::const_iterator end = this->_clients.end();
	for (std::vector<Client *>::iterator it = this->_clients.begin(); it != end; it++)
		if (*it) { delete *it; *it = NULL; }
	this->_clients.clear();
}

/*Server::~Server()
{
	Trie<std::vector<std::string> >	helpMessage;
	std::vector<std::string> vec;
	vec.push_back("NICK => is a function");
	vec.push_back()
	this->helpMessage.add("NICK", vec);
	this->helpMessage[cmd]
	const std::vector<Client *>::const_iterator end = this->_clients.end();
	for (std::vector<Client *>::iterator it = this->_clients.begin(); it != end; it++)
		if (*it) { delete *it; *it = NULL; }
	this->_clients.clear();
}*/

bool    Server::_validateAccess(Client &c, std::string &command)
{
	if (command=="CAP" || command == "PASS" || command == "NICK" || command == "USER" || command == "QUIT")
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

void	Server::disconnectClient(int fd, std::string error, std::string message) {
	Client	&c = this->getClient(fd);
	if (!error.empty())
		this->sendToClient(c, error);
	if (!c.getBufferOut().empty())
		c.quitRequest = CLIENT_QUIT_REQUEST;
	else
		c.quitRequest = CLIENT_QUIT_ACCEPT;
	c.setBufferQuit(message);
	this->poolQuit.push_back(fd);
}

void	Server::_autoKill(Client &c, std::string message)
{
	std::string	serverName(":" + this->_host);
	std::string	killed("Killed (");
	killed.append("auto-kill (").append(message).append("))");
	std::string	rplError(serverName);
	rplError.append(" ERROR: Closing Link: ").append(c.getNick()).append(1, ' ').append(this->_host).append(" (").append(killed).append(")\r\n");
	std::string	rplQuit(this->_makeHostMask(c, "QUIT"));
	rplQuit.append(":Quit: ").append(killed).append("\r\n");
	std::string	rplKill(serverName);
	rplKill.append(" KILL ").append(c.getNick()).append(" :").append(message).append("\r\n");
	c.addBufferOut(rplKill);
	c.addBufferOut(rplQuit);
	this->disconnectClient(c.getFd(), rplError, rplQuit);
}

bool	Server::doCommand(size_t fd)
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
		if (!this->_validateAccess(*c, cmd) || !this->_validateCommand(*c, func, cmd))
		{
			serverReceivesLogError(c->buffer.substr(0, index), "not valid");
			const int warnings = c->getWarning() + 1;
			c->setWarning(warnings);
			#ifndef UNITTEST
			if (warnings >= WARNING_LIMIT)
				this->_autoKill(*c, "Killed by server, too many bad commands");
			#endif
			if (c->getNick().empty())
				std::cout << fd << ": You get a warning (" << warnings << ")" << std::endl;
			else
				std::cout << c->getNick() << ": You get a warning (" << warnings << ")" << std::endl;
			continue ;
		}
		serverReceivesLog(sanitizedClientBuffer);
		(this->*func)(*c, iss);
	}
}

static int ClientOnServerAccessType(char c, AccessType &flag)
{
	switch (c)
	{
		case 'i':
			flag = CLIENT_ACCESS_INVISIBLE;
			return (true);
		case 'x':
			flag = CLIENT_ACCESS_HIDDEN_HOST;
			return (true);
		case 'd':
			flag = CLIENT_ACCESS_DEAF;
			return (true);
		case 'R':
			flag = CLIENT_ACCESS_REGISTERED;
			return (true);
		case 'g':
			flag = CLIENT_ACCESS_WHITELIST;
			return (true);
		case 'B':
			flag = CLIENT_ACCESS_BOT;
			return (true);
		case 'o': case 'O':
			flag = CLIENT_ACCESS_OPERATOR;
			return (true);
		case 'a': case 'A':
			flag = CLIENT_ACCESS_ADMIN;
			return (true);
		default:
			return (false);
	}
	return (false);
}

bool	Server::handleModeUser(Client &c, std::string targetName, std::string modeType, std::string &message)
{
	int clientFd = -1;
	try {
		clientFd = this->_clientTrie[targetName];
	} catch (std::exception &e) {
		return (this->handleErrNoSuchNick(c, targetName), this->poolOut.push(c.getFd()), false);
	}
	if (modeType.empty())
	{
		if (clientFd != c.getFd())
			return (this->handleErrUsersDontMatch(c), this->poolOut.push(c.getFd()), false);
		return (this->handleRplUModeIs(c), this->poolOut.push(clientFd), true);
	}
	if (modeType[0] != '+' && modeType[0] != '-')
			return (this->handleErrUmodeunknownflag(c), this->poolOut.push(c.getFd()), false);
	bool plusOrMinus = (modeType[0] == '+');
	unsigned int i = 0;
	message.append(1, modeType[i]);
	while (modeType[++i])
	{
		if (modeType[i] == '+' || modeType[i] == '-')
		{
			plusOrMinus = (modeType[i] == '+');
			message.append(1, modeType[i]);
			continue ;
		}
		AccessType flag = 0;
		if (!ClientOnServerAccessType(modeType[i], flag))
			continue ;
    	if (plusOrMinus)
		{
			if (!(modeType[i] == 'o' || modeType[i] == 'O' || modeType[i] == 'a' || modeType[i] == 'A')) // peut pas s'add en admin
			{
    	    	c.addStatus(flag);
				message.append(1, modeType[i]);
			}
		}
    	else
		{
			if (!(modeType[i] == 'B')) // peut pas s'enlever de bot
			{
    	    	c.delStatus(flag);
				message.append(1, modeType[i]);
			}
		}
	}
	return (true);
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

bool	Server::sendToChannel(Channel &source, std::string message)
{
	std::vector<int>	&clients = source.getClientsFD();
	for (std::vector<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
		Client	&c = this->getClient(*it);
		c.addBufferOut(message);
		this->poolOut.push(c.getFd());
	}
	return (true);
}

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
	this->poolOut.push(c.getFd());
}

bool _constantTimeCheck(const std::string &pass, const std::string &toCheck)
{
	unsigned char diff = 0;
	for (unsigned int i = 0; i < pass.size(); i++) {
		diff |= static_cast<unsigned char>(pass[i] ^ toCheck[i]);
	}
	return (diff == 0);
}
