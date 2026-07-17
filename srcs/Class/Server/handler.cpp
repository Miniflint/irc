#include "Server.hpp"
#include <cstring>
#include <algorithm>

std::string	Server::_makeHostMask(Client &c, std::string functionName)
{
	std::string rtn;
	const size_t totalSize = rtn.size() + 5 + c.getNick().size() +
		c.getUserName().size() + c.getHostName().size() + functionName.size();

	rtn.reserve(totalSize);
	rtn.append(1, ':').append(c.getNick()).append(1, '!').append(c.getUserName())
		.append(1, '@').append(c.getHostName()).append(1, ' ').append(functionName)
		.append(1, ' ');
	return (rtn);
}
/* 
static std::string	_formatBaseServerMessage(Server &serv, Client &c, std::string code)
{
	std::string rtn;

	const size_t totalSize = 5 + serv.getIp().size() + code.size() + c.getNick().size();
	rtn.reserve(totalSize);
	rtn.append(1, ' ').append(serv.getIp()).append(1, ' ').append(code)
		.append(1, ' ').append(c.getNick()).append(1, ' ').append(1, ':');
	return (rtn);
}
*/
bool	Server::handle_admin(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "ADMIN");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_away(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "AWAY");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_cap(Client &c, std::istringstream &iss) 
{
	(void)c;
	(void)iss;
	return (true);
}
bool	Server::handle_cnotice(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "CNOTICE");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_cprivmsg(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "CPRIVMSG");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_connect(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "CONNECT");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_die(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "DIE");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_error(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "ERROR");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_help(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "HELP");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handleInfo(Client &c, std::istringstream &iss) 
{
	(void)iss;
	this->handleRplInfo(c, INFO_MSG_TAG0);
	this->handleRplInfo(c, INFO_MSG_TAG1);
	this->handleRplInfo(c, INFO_MSG_TAG2);
	this->handleRplInfo(c, INFO_MSG_TAG3);
	this->handleRplInfo(c, INFO_MSG_TAG4);
	this->handleRplInfo(c, INFO_MSG_TAG5);
	this->handleRplInfo(c, INFO_MSG_TAG6);
	this->handleRplInfo(c, INFO_MSG_TAG7);
	this->handleRplInfo(c, INFO_MSG_TAG8);
	this->handleRplInfo(c, INFO_MSG_TAG9);
	this->handleRplInfo(c, INFO_MSG_DATE);
	this->handleRplInfo(c, INFO_MSG_VERSION);
	this->handleRplEndofinfo(c);
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_invite(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "INVITE");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_ison(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "ISON");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handleJoin(Client &c, std::istringstream &iss) 
{
	std::string channel, key;
	iss >> channel >> key;
	if (channel.empty())
		return (this->handleErrNeedMoreParams(c, "JOIN"), this->poolOut.push(c.getFd()), false);
	std::istringstream			channelParse(channel), keyParse(key);
	std::vector<std::string>	channelList, keyList;
	for (std::string tmp; std::getline(keyParse, tmp, ',');)
		keyList.push_back(tmp);
	for (std::string tmp; std::getline(channelParse, tmp, ',');)
		channelList.push_back(tmp);
	std::vector<std::string>::iterator end = channelList.end();
	unsigned int i = 0;
	for (std::vector<std::string>::iterator it = channelList.begin(); it != end; it++) {
		std::string channelName = *it;
		if (i < keyList.size()) {
			this->addClientToChannel(c, channelName, keyList[i]);
			++i;
		} else
			this->addClientToChannel(c, channelName, "");
		// if (!keyList.empty())
		// {
		// 	size_t index = i > keyList.size() - 1 ? keyList.size() - 1 : i;
		// 	if (this->addClientToChannel(c, channelName, keyList[index]) == NULL)
		// 		this->poolOut.push(c.getFd());
		// } else {
		// 	if (this->addClientToChannel(c, channelName, "") == NULL)
		// 		this->poolOut.push(c.getFd());
		// }
		// i++;
	}
	return (true);
}
bool	Server::handle_kick(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "KICK");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_kill(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "KILL");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_knock(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "KNOCK");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_links(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "LINKS");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handleList(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	if (token.empty())
	{
		this->handleRplListStart(c);
		this->handleRplList(c);
		this->handleRplListEnd(c);
		this->poolOut.push(c.getFd());
		return (true);
	}
	return (true);
}
bool	Server::handle_lusers(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "LUSERS");
	this->poolOut.push(c.getFd());
	return (true);
}

/*

+qXgk-r
while (mode)
switch (mode[i])
{
	'+':
		FONCTION_PLUS(mode, i, iss)
	'-':
		FONCTION_MOINS
	default:
		FONCTION_NON_PLUS
}
*/

bool	Server::handleMode(Client &c, std::istringstream &iss) 
{
	std::string 				targetName, modeType;
	iss >> targetName >> modeType;
	if (targetName.empty())
		return (this->handleErrNeedMoreParams(c, "MODE"), this->poolOut.push(c.getFd()), false);
	bool	channelOrClient = this->_channelSpecifiers.channelType.find(targetName[0]) == std::string::npos;
	if (channelOrClient)
	{
		if (!handleModeUser(c, targetName, modeType))
			return (false);
		std::string	message(this->_makeHostMask(c, "MODE"));
		message.append(1, ':').append(targetName).append(1, ' ').append(modeType).append("\r\n");
		this->sendToClient(c, message);
	}
	else
	{
		Channel *channel = NULL;
		try {
			channel = this->_channelTrie[targetName];
		} catch (std::exception &e) {
			return (this->handleErrNoSuchChannel(c, targetName), this->poolOut.push(c.getFd()), false);
		}
		if (modeType.empty())
		{
			std::string	message(this->_makeHostMask(c, "MODE"));
			message.append(1, ':').append(targetName).append(1, ' ').append(modeType).append("\r\n");
			this->sendToClient(c, message);
			return (this->handleRplChannelModeIs(c, *channel), this->poolOut.push(c.getFd()), true);
		}
		if (modeType[0] != '+' && modeType[0] != '-')
				return (this->handleErrUmodeunknownflag(c), this->poolOut.push(c.getFd()), false);
		int i = 0;
		bool checkErrorOnce = false;
		while (modeType[i])
		{
			switch (modeType[i])
			{
				case '+':
					this->_handleCaseAdd(c, modeType, &i, *channel, iss);
					break ;
				case '-':
					this->_handleCaseDel(c, modeType, &i, *channel, iss);
					break ;
				default:
					break ;
			}
		}
		if (checkErrorOnce)
			return (this->poolOut.push(c.getFd()), false);
	}
	return (true);
}

bool	Server::handle_motd(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "MOTD");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_names(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "NAMES");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handleNick(Client &c, std::istringstream &iss) 
{
	if (!(c.flagsLogin & FLAG_CLIENT_PASS))
		return (this->handleErrNotregistered(c), this->poolOut.push(c.getFd()), false);
	std::string token;

	iss >> token;
	if (iss.fail() || token.empty())
		return (this->handleErrNoNicknameGiven(c), this->poolOut.push(c.getFd()), false);
	if (token.length() > this->_clientSpecifiers.nickLenMax)
		return (this->handleErrErroneousNickname(c, token), this->poolOut.push(c.getFd()), false);
	if (token[0] == ':' || this->_channelSpecifiers.channelType.find(token[0]) != std::string::npos)
		return (this->handleErrNickCollision(c, token), this->poolOut.push(c.getFd()), false);
	if (this->_clientTrie.isIn(token))
		return (this->handleErrNicknameInUse(c, token), this->poolOut.push(c.getFd()), false);
	std::string oldUserName = c.getNick();
	if (c.flagsLogin == FLAG_CLIENT_FULL)
	{
		std::list<Channel>::iterator end = this->_channel.end();
		for (std::list<Channel>::iterator it = this->_channel.begin(); it != end; it++) {
			if (std::find((*it).getClientsFD().begin(), (*it).getClientsFD().end(), c.getFd()) != (*it).getClientsFD().end())
			{
				std::string rplMessage(this->_makeHostMask(c, "NICK"));
				rplMessage.append(token).append(" :Changed nickname from [").append(oldUserName);
				rplMessage.append("] to [").append(token).append("]\r\n");
				this->sendToChannel((*it), rplMessage);
			}
		}
		this->_clientTrie.del(oldUserName);
		// faire message pour changement de nom
	}
	c.setNick(token);
	if (c.flagsLogin & FLAG_CLIENT_USER)
	{
		this->_clientTrie.add(token, c.getFd());
		if (!(c.flagsLogin & FLAG_CLIENT_NICK))
			this->_sendAllWelcome(c);
	}
	c.flagsLogin |= FLAG_CLIENT_NICK;
	return (true);
}
bool	Server::handle_notice(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "NOTICE");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handleOper(Client &c, std::istringstream &iss) 
{
	std::string name, pass;
	iss >> name >> pass;
	if (name.empty() || pass.empty())
		return (this->handleErrNeedMoreParams(c, "OPER"), this->poolOut.push(c.getFd()), false);
	if (name == this->_adminName && pass == this->_adminPass) {
		c.addStatus(CLIENT_ACCESS_ADMIN | CLIENT_ACCESS_OPERATOR);
		return (this->handleRplYoureOper(c, "You are now an IRC admin"), this->poolOut.push(c.getFd()), false);
	}
	if (name == this->_operatorName && pass == this->_operatorPass) {
		c.addStatus(CLIENT_ACCESS_OPERATOR);
		return (this->handleRplYoureOper(c, "You are now an IRC operator"), this->poolOut.push(c.getFd()), false);
	}
	this->handleErrPasswdMismatch(c);
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handlePart(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	if (iss.fail() || token.empty())
		return (this->handleErrNeedMoreParams(c, "PASS"), this->poolOut.push(c.getFd()), false);
	Trie<Channel *>	*channelTrie = this->_channelTrie.find(token);
	if (!channelTrie)
		return (this->handleErrNoSuchChannel(c, token), this->poolOut.push(c.getFd()), false);
	if (!c.getChannel().isIn(token))
		return (this->handleErrNotOnChannel(c, token), this->poolOut.push(c.getFd()), false);
	Channel	&channel = *channelTrie->getElem();
	this->delClientToChannel(c, channel, this->_makeHostMask(c, "PART").append(token).append(" :").append(iss.str()).append("\r\n"));
	// this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handlePass(Client &c, std::istringstream &iss) 
{
	if (c.flagsLogin & FLAG_CLIENT_PASS)
		return (this->handleErrAlreadyRegistered(c) ,this->poolOut.push(c.getFd()), false);
	std::string token;
	iss >> token;
	if (iss.fail() || token.empty())
		return (this->handleErrNeedMoreParams(c, "PASS") ,this->poolOut.push(c.getFd()), false);
	if (this->_password.size() != token.size() || !_constantTimeCheck(this->_password, token))
		return (this->handleErrPasswdMismatch(c) ,this->poolOut.push(c.getFd()), false);
	c.flagsLogin |= FLAG_CLIENT_PASS;
	return (true);
}
bool	Server::handlePing(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	if (iss.fail() || token.empty())
		return (this->handleErrNeedMoreParams(c, "PING"), this->poolOut.push(c.getFd()), false);
	std::string	pongRet = ":";
	pongRet.append(this->_host).append(" PONG ").append(this->_host).append(" ").append(token).append("\r\n");
	this->sendToClient(c, pongRet);
	return (true);
}
bool	Server::handle_pong(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "PONG");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handlePrivMsg(Client &c, std::istringstream &iss) 
{
	std::string target, message;
	iss >> target;
	if (iss.fail() || target.empty())
		return (this->handleErrNoRecipient(c, "PRIVMSG"), this->poolOut.push(c.getFd()), false);
	iss >> message;
	if (message.empty() || (message.size() == 1 && message[0] == ':'))
		return (this->handleErrNoTextToSend(c), this->poolOut.push(c.getFd()), false);
	if (message[0] == ':') {
		std::string buff;
		std::getline(iss, buff);
		message += buff;
	}
	std::vector<size_t>	clients;
	std::string realTarget(target);
	if (this->_channelSpecifiers.channelType.find(target[0]) != std::string::npos)
	{
		Channel	*targetChannel = NULL;
		try {
			targetChannel = c.getChannel()[target].first;
		} catch (std::exception &e) {
			try {
				targetChannel = this->_channelTrie[target];
			} catch (std::exception &e) {
				return (this->handleErrNoSuchChannel(c, target), this->poolOut.push(c.getFd()), false);
			}
			if (!targetChannel->checkMode(CHANNEL_NOT_EXTERNAL))
				return (this->handleErrCannotSendToChan(c, target), this->poolOut.push(c.getFd()), false);
		}
		AccessType t = c.getChannelAccess(targetChannel->getNick());
		if (targetChannel->checkMode(CHANNEL_MODERATED) && t == NO_ACCESS)
				return (this->handleErrCannotSendToChan(c, target), this->poolOut.push(c.getFd()), false);
		clients.assign(targetChannel->getClientsFD().begin(), targetChannel->getClientsFD().end());
	}
	else
	{
		size_t targetClient	= 0;
		try {
			targetClient = this->_clientTrie[target];
		} catch (std::exception &e) {
			return (this->handleErrNoSuchNick(c, target), this->poolOut.push(c.getFd()), false);
		}
		clients.push_back(targetClient);
		clients.push_back(c.getFd());
	}
	std::string		full(_makeHostMask(c, "PRIVMSG"));
	// message.erase(0, 1);
	full.append(target).append(1, ' ').append(message).append("\r\n");
	std::vector<size_t>::const_iterator end = clients.end();
	for (std::vector<size_t>::const_iterator it = clients.begin(); it != end; it++) {
		Client *curr = this->_clients[*it];
		if (!curr)
			continue ;
		this->sendToClient(*curr, full);
	}
	return (true);
}
bool	Server::handleQuit(Client &c, std::istringstream &iss) 
{
	std::string token;

	std::getline(iss, token);
	std::string message(":");
	message.append(c.getNick()).append(1, '!').append(c.getUserName()).append(1, '@').append(c.getHostName()).append(" QUIT :");
	if (token.empty())
		token += "Left without a message";
	if (token[0] == ':')
		token.erase(0, 1);
	token.append("\r\n");
	this->deconnectClient(c.getFd(), message + "Thanks for being with us\r\n", message + token);
	return (true);
}
bool	Server::handle_quote(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "QUOTE");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_rehash(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "REHASH");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_rules(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "RULES");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_server(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "SERVER");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_squery(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "SQUERY");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_squit(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "SQUIT");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_setname(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "SETNAME");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_silence(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "SILENCE");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_stats(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "STATS");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_summon(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "SUMMON");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_time(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "TIME");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_topic(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "TOPIC");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_trace(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "TRACE");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handleUser(Client &c, std::istringstream &iss) 
{

	if (!(c.flagsLogin & FLAG_CLIENT_PASS))
		return (this->handleErrNotregistered(c), this->poolOut.push(c.getFd()), false);
	if (c.flagsLogin & FLAG_CLIENT_USER)
		return (this->handleErrAlreadyRegistered(c), this->poolOut.push(c.getFd()), false);
 
	std::string userName, hostName, serverName, realName;
	if (!(iss >> userName >> hostName >> serverName)
		|| userName.empty() || hostName.empty() || serverName.empty())
		return (this->handleErrNeedMoreParams(c, "USER"), this->poolOut.push(c.getFd()), false);
	std::getline(iss, realName);
	if (realName.empty())
		return (this->handleErrNeedMoreParams(c, "USER"), this->poolOut.push(c.getFd()), false);
	size_t indexTrim = realName.find_first_not_of(' ');
	if (indexTrim == std::string::npos)
		return (this->handleErrNeedMoreParams(c, "USER"), this->poolOut.push(c.getFd()), false);
	realName.erase(0, indexTrim + 1);
	if (userName.length() < 1 || hostName.length() < 1 || serverName.length() < 1 || realName.length() < 1)
		return (this->handleErrNeedMoreParams(c, "USER"), this->poolOut.push(c.getFd()), false);
	c.setUserName(userName);
	// c.setHostName(hostName);
	c.setServerName(serverName);
	c.setRealName(realName);
	if (c.flagsLogin & FLAG_CLIENT_NICK)
	{
		this->_clientTrie.add(c.getNick(), c.getFd());
		this->_sendAllWelcome(c);
	}
	c.flagsLogin |= FLAG_CLIENT_USER;
	return (true);
}
bool	Server::handle_userhost(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "USERHOST");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_userip(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "USERIP");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_users(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "USERS");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_version(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "VERSION");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_wallops(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "WALLOPS");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_watch(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "WATCH");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handleWho(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	if (token.empty())
		return (false);
	try {
		Channel	*chan = c.getChannel()[token].first;
		for (std::vector<int>::iterator it = chan->getClientsFD().begin(); it != chan->getClientsFD().end(); ++it)
			this->handleRplWhoReply(c, this->getClient(*it), *chan);
	} catch (std::exception &e) { (void)e; }
	this->handleRplEndOfWho(c, token);
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_whois(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "WHOIS");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_whowas(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "WHOWAS");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handleDcc(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "DCC");
	this->poolOut.push(c.getFd());
	return (true);
}
bool	Server::handle_message(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	this->handleErrUnknowncommand(c, "MESSAGE");
	this->poolOut.push(c.getFd());
	return (true);
}
