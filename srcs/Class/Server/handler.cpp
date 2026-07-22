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
bool	Server::handleCap(Client &c, std::istringstream &iss) 
{
	std::string typeCap;

	if (c.flagsLogin == FLAG_CLIENT_FULL)
		return (this->handleErrAlreadyRegistered(c), this->poolOut.push(c.getFd()), false);
	if (!(iss >> typeCap))
		return (this->handleErrNeedMoreParams(c, "CAP"), this->poolOut.push(c.getFd()), false);
	if (typeCap == "LS")
	{
		int versionCap;
		if (!(iss >> versionCap) || versionCap > 302)
			versionCap = 300;
		if (versionCap == 302)
			c.flagsLogin |= FLAG_CLIENT_CAPL;
	}
	if (typeCap == "REQ" && c.flagsLogin & FLAG_CLIENT_CAPL)
	{
		std::string tokenRequested;
		std::string rplMessage(this->_rplPrefix("CAP", "*"));
		if (!(iss >> tokenRequested))
		{
			rplMessage.append("NAK :\r\n");
			return (c.addBufferOut(rplMessage), this->poolOut.push(c.getFd()), false);
		}
		if (tokenRequested[0] == ':')
			tokenRequested.erase(0, 1);
		if (tokenRequested == "echo-message")
		{
			c.addStatus(CLIENT_ECHO_MESSAGE);
			rplMessage.append("ACK ").append(tokenRequested).append("\r\n");
			return (c.addBufferOut(rplMessage), this->poolOut.push(c.getFd()), false);
		}
		else
		{
			rplMessage.append("NAK :").append(tokenRequested).append("\r\n");
			return (c.addBufferOut(rplMessage), this->poolOut.push(c.getFd()), false);
		}
	}
	if (typeCap == "END" && c.flagsLogin & FLAG_CLIENT_CAPL)
		c.flagsLogin &= ~FLAG_CLIENT_CAPL;
	if (c.flagsLogin == FLAG_CLIENT_FULL)
	{
		this->_clientTrie.add(c.getNick(), c.getFd());
		this->_sendAllWelcome(c);
	}
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
bool	Server::handleDie(Client &c, std::istringstream &iss) 
{
	(void)iss;
	if (c.getStatus() < CLIENT_ACCESS_OPERATOR)
		return (this->handleErrNoPrivileges(c), this->poolOut.push(c.getFd()), false);
	this->runStatus = RUN_SHUTDOWN;
	return (true);
}

bool	Server::handleRestart(Client &c, std::istringstream &iss) 
{
	(void)iss;
	if (c.getStatus() < CLIENT_ACCESS_OPERATOR)
		return (this->handleErrNoPrivileges(c), this->poolOut.push(c.getFd()), false);
	this->runStatus = RUN_RESTART;
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
bool	Server::handleInvite(Client &c, std::istringstream &iss) 
{
	std::string nickname, channelName;
	iss >> nickname >> channelName;
	if (iss.fail() || nickname.empty() || channelName.empty())
		return (this->handleErrNeedMoreParams(c, "INVITE"), this->poolOut.push(c.getFd()), false);
	Trie<Channel *>	*channelTrie = this->_channelTrie.find(channelName);
	if (!channelTrie)
		return (this->handleErrNoSuchChannel(c, channelName), this->poolOut.push(c.getFd()), false);
	Trie<int> *clientTrie = this->_clientTrie.find(nickname);
	if (!clientTrie)
		return (this->handleErrNoSuchNick(c, channelName), this->poolOut.push(c.getFd()), false);
	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && !c.getChannel().isIn(channelName))
		return (this->handleErrNotOnChannel(c, channelName), this->poolOut.push(c.getFd()), false);
	Channel *chan = channelTrie->getElem();
	if (chan->getMode() & CHANNEL_INVITE_ONLY &&
		(c.getStatus() < CLIENT_ACCESS_OPERATOR) && c.getChannelAccess(channelName) < USER_HALFOP)
		return (this->handleErrChanOPrivsNeeded(c, channelName), this->poolOut.push(c.getFd()), false);
	chan->addClientException(clientTrie->getElem(), EXCEPTION_INVITED);
	Client	&receiver = *(this->_clients[clientTrie->getElem()]);
	this->sendToClient(receiver, this->_makeHostMask(c, "INVITE").append(receiver.getNick())
		.append(1, ' ').append(channelName).append("\r\n"));
	return (this->handleRplInviting(c, nickname, channelName, 0), this->poolOut.push(c.getFd()), true);
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
		if (i < keyList.size())
			this->addClientToChannel(c, channelName, keyList[i++]);
		else
			this->addClientToChannel(c, channelName, "");
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
		if (modeType.empty())
			message.append(1, ':').append(targetName).append("\r\n");
		else
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
		std::string fullStr(this->_makeHostMask(c, "MODE"));
		std::string letters(1, modeType[i]);
		std::string usedTokens;
		while (modeType[i])
		{
			switch (modeType[i])
			{
				case '+':
					if (this->_handleCaseAdd(c, modeType, &i, *channel, iss, letters, usedTokens) && modeType[i])
						letters.append(1, modeType[i]);
					break ;
				case '-':
					if (this->_handleCaseDel(c, modeType, &i, *channel, iss, letters, usedTokens) && modeType[i])
						letters.append(1, modeType[i]);
					break ;
				default:
					break ;
			}
		}
		size_t index = usedTokens.find_first_not_of(' ');
		fullStr.append(channel->getNick()).append(1, ' ').append(letters);
		if (index != std::string::npos)
			fullStr.append(usedTokens).append("\r\n");
		else
			fullStr.append("\r\n");
		this->sendToChannel(*channel, fullStr);
		if (checkErrorOnce)
			return (false);
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
	}
	c.setNick(token);
	if (!(c.flagsLogin & FLAG_CLIENT_NICK)) {
		c.flagsLogin |= FLAG_CLIENT_NICK;
		if (c.flagsLogin == (FLAG_CLIENT_FULL | FLAG_CLIENT_CAPL))
		{
			std::string rplMessage(this->_rplPrefix("CAP", "* LS"));
			rplMessage.append(":echo-message\r\n");
			c.addBufferOut(rplMessage);
			this->poolOut.push(c.getFd());
		}
		else if (c.flagsLogin == FLAG_CLIENT_FULL)
		{
			this->_sendAllWelcome(c);
			this->_clientTrie.add(token, c.getFd());
		}
	}
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
		return (this->handleErrNeedMoreParams(c, "PART"), this->poolOut.push(c.getFd()), false);
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
			if (c.getStatus() < CLIENT_ACCESS_OPERATOR && targetChannel->getMode() & CHANNEL_NOT_EXTERNAL)
				return (this->handleErrCannotSendToChan(c, target), this->poolOut.push(c.getFd()), false);
		}
		AccessType t = c.getChannelAccess(target);
		std::cout << "client channel access =>" << t << " client status =>" << c.getStatus() << " channel mode =>" << targetChannel->getMode() << std::endl;
		std::cout << "bool resulet : client channel access =>" << bool(t < USER_VOICE) << "client status =>" << bool(c.getStatus() < CLIENT_ACCESS_OPERATOR) << "channel mode =>" << bool(targetChannel->getMode() & CHANNEL_MODERATED) << std::endl;
		if (c.getStatus() < CLIENT_ACCESS_OPERATOR && targetChannel->getMode() & CHANNEL_MODERATED && t < USER_VOICE)
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
		if (!curr || (!(curr->getStatus() & CLIENT_ECHO_MESSAGE) && curr->getFd() == c.getFd()))
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
		token = "Left without a message";
	if (token[0] == ':')
		token.erase(0, 1);
	token.append("\r\n");
	std::string rplSelfMessage(message);
	rplSelfMessage.append("Quit: Thanks for being with us\r\n");
	std::string rplChannelsMessages(message);
	rplChannelsMessages.append("Quit: ");
	rplChannelsMessages.append(token);
	this->disconnectClient(c.getFd(), rplSelfMessage, rplChannelsMessages);
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


bool	Server::handleTopic(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	if (iss.fail() || token.empty())
		return (this->handleErrNeedMoreParams(c, "TOPIC"), this->poolOut.push(c.getFd()), false);
	if (!this->_channelTrie.isIn(token))
		return (this->handleErrNoSuchChannel(c, token), this->poolOut.push(c.getFd()), false);
	Trie<std::pair<Channel *, AccessType> >	*channelTrieElem = c.getChannel().find(token);
	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && !channelTrieElem)
		return (this->handleErrNotOnChannel(c, token), this->poolOut.push(c.getFd()), false);
	std::string	newTopic;
	iss >> newTopic;
	Channel	&chan = *(channelTrieElem->getElem().first);
	std::string	&chanTopic = chan.getTopic();
	if (newTopic.empty()) {
		if (chanTopic.empty())
			return (this->handleRplNoTopic(c, token), this->poolOut.push(c.getFd()), true);
		else
			return (this->handleRplTopic(c, token, chanTopic), this->poolOut.push(c.getFd()), true);
	}
	if (chan.checkMode(CHANNEL_TOPIC_PROTECTION) && c.getStatus() < CLIENT_ACCESS_OPERATOR && channelTrieElem->getElem().second < USER_HALFOP)
		return (this->handleErrChanOPrivsNeeded(c, token), this->poolOut.push(c.getFd()), false);
	if (newTopic[0] == ':') {
		newTopic.erase(0, 1);
		std::string	rest;
		std::getline(iss, rest);
		newTopic.append(rest);
	}
	chanTopic = newTopic;
	this->sendToChannel(chan, this->_makeHostMask(c, "TOPIC").append(token).append(" :").append(chanTopic).append("\r\n"));
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
	realName.erase(0, indexTrim);
	if (!realName.empty() && realName[0] == ':')
		realName.erase(0, 1);
	if (/*userName.empty() || hostName.empty() || serverName.empty() || */realName.empty())
		return (this->handleErrNeedMoreParams(c, "USER"), this->poolOut.push(c.getFd()), false);
	c.setUserName(userName);
	// c.setHostName(hostName);
	c.setServerName(serverName);
	c.setRealName(realName);
	c.flagsLogin |= FLAG_CLIENT_USER;
	if (c.flagsLogin == FLAG_CLIENT_FULL)
	{
		this->_clientTrie.add(c.getNick(), c.getFd());
		this->_sendAllWelcome(c);
	}
	else if (c.flagsLogin == (FLAG_CLIENT_FULL | FLAG_CLIENT_CAPL))
	{
		std::string rplMessage(this->_rplPrefix("CAP", "* LS"));
		rplMessage.append(":echo-message\r\n");
		c.addBufferOut(rplMessage);
		this->poolOut.push(c.getFd());
	}
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
		return (this->handleErrNeedMoreParams(c, "WHO"), this->poolOut.push(c.getFd()), false);
	if (this->_channelSpecifiers.channelType.find(token[0]) != std::string::npos)
	{
		Trie<Channel *> *trieClientChan = this->_channelTrie.find(token);
		if (trieClientChan) {
			Channel	&chan = *(trieClientChan->getElem());
			// if (c.getStatus() < CLIENT_ACCESS_OPERATOR && !c.getChannel().isIn(token))
			// 	return (this->handleErrNotOnChannel(c, token), this->poolOut.push(c.getFd()), false);
			for (std::vector<int>::iterator it = chan.getClientsFD().begin(); it != chan.getClientsFD().end(); ++it) {
				if (c.getStatus() < CLIENT_ACCESS_OPERATOR && c.getChannelAccess(token) < USER_HALFOP && this->_clients[*it]->checkStatus(CLIENT_ACCESS_INVISIBLE))
					continue ;
				this->handleRplWhoReply(c, this->getClient(*it), chan);
			}
		}/* else
			return (this->handleErrNoSuchChannel(c, token), this->poolOut.push(c.getFd()), false); */
	}/* else {
		Trie<int> *trieClient = this->_clientTrie.find(token);
		if (trieClient) {
			Client	&whoClient = *(this->_clients[trieClient->getElem()]);
			if (!(c.getStatus() < CLIENT_ACCESS_OPERATOR && whoClient.checkStatus(CLIENT_ACCESS_INVISIBLE)))
				this->handleRplWhoReply(c, whoClient, chan);
		}
	} */
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
