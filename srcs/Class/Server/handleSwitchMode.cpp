#include "Server.hpp"

int	Server::_bCaseAdd(Client &c, Channel &channel, std::istringstream &iss, AccessType userAccessOnChannel, std::string &usedToken)
{
    const std::string channelName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_OPERATOR)
		return (this->handleErrChanOPrivsNeeded(c, channelName), false);
	std::string userTarget;

	iss >> userTarget;
	if (iss.fail() || userTarget.empty())
	{
		channel.addMode(CHANNEL_BAN);
		const std::map<int, AccessType>::const_iterator end = channel.getClientException().end();
		for (std::map<int, AccessType>::const_iterator it = channel.getClientException().begin(); it != end; it++) {
		const std::string targetName = (*this->_clients[(*it).first]).getNick();
		std::string rplMessage(this->_makeHostMask(c, "MODE"));
		rplMessage.append("has banned ").append(targetName).append("\r\n");
			if ((*it).second & EXCEPTION_BANNED)
				this->delClientToChannel(*this->_clients[(*it).first], channel, rplMessage);
		}
		this->handleRplBanList(c, channel);
		this->handleRplEndofbanlist(c, channelName);
		return (2);
	}
	Trie<int>	*trieClient;
	if (!(trieClient = this->_clientTrie.find(userTarget)))
		return (false);
	int bannedClient = trieClient->getElem();
	if (bannedClient > 0)
	{
		const std::string targetName = (*this->_clients[bannedClient]).getNick();
		std::string rplMessage(this->_makeHostMask(c, "MODE"));
		rplMessage.append("has banned ").append(targetName).append("\r\n");
		this->delClientToChannel(*this->_clients[bannedClient], channel, rplMessage);
	}
	usedToken.append(1, ' ').append(userTarget);
	channel.addMode(CHANNEL_BAN);
	channel.addClientException(bannedClient, EXCEPTION_BANNED);
	return (true);
}

int	Server::_bCaseDel(Client &c, Channel &channel, std::istringstream &iss, AccessType userAccessOnChannel, std::string &usedToken)
{
    const std::string channelName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_OPERATOR)
		return (this->handleErrChanOPrivsNeeded(c, channelName), false);
	std::string userTarget;

	iss >> userTarget;
	if (iss.fail() || userTarget.empty())
		return (channel.delMode(CHANNEL_BAN), 2);
	int bannedClient = -1;
	Trie<int>	*trieClient;
	if (!(trieClient = this->_clientTrie.find(userTarget)))
		return (false);
	bannedClient = trieClient->getElem();
	if (bannedClient > 0)
	{
		const std::string targetName = (*this->_clients[bannedClient]).getNick();
		std::string rplMessage(this->_makeHostMask(c, "MODE"));
		rplMessage.append("has unbanned ").append(targetName).append("\r\n");
		this->sendToChannel(channel, rplMessage);
	}
	usedToken.append(1, ' ').append(userTarget);
	channel.delClientException(bannedClient, EXCEPTION_BANNED);
	return (true);
}


bool	Server::_lCaseAdd(Client &c, Channel &channel, std::istringstream &iss, AccessType userAccessOnChannel, std::string &usedToken)
{
    const std::string targetName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_HALFOP)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
	int r;
	iss >> r;
	if (iss.fail())
		return (this->handleErrNeedMoreParams(c, "MODE"), this->poolOut.push(c.getFd()), false);

	std::ostringstream token;
	token << r;
	usedToken.append(1, ' ').append(token.str());
	channel.setMaxUsers(r);
	channel.addMode(CHANNEL_LIMIT_USER);
    return (true);
}

bool	Server::_lCaseDel(Client &c, Channel &channel, AccessType userAccessOnChannel)
{
    const std::string targetName = channel.getNick();
 
	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_HALFOP)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);

	channel.delMode(CHANNEL_LIMIT_USER);
    return (true);
}

bool	Server::_kCaseAdd(Client &c, Channel &channel, std::istringstream &iss, AccessType userAccessOnChannel, std::string &usedToken)
{
    const std::string targetName = channel.getNick();

    if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_OPERATOR)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
    std::string nextToken;
	if (!(iss >> nextToken))
		return (this->handleErrNeedMoreParams(c, "MODE"), this->poolOut.push(c.getFd()), false);

	usedToken.append(1, ' ').append(nextToken);
	channel.setPass(nextToken);
	channel.addMode(CHANNEL_KEY);
	return (true);
}

bool	Server::_kCaseDel(Client &c, Channel &channel, std::istringstream &iss, AccessType userAccessOnChannel, std::string &usedToken)
{
    const std::string targetName = channel.getNick();
    if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_OPERATOR)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
    std::string nextToken;
	if (!(iss >> nextToken))
		return (this->handleErrNeedMoreParams(c, "MODE"), this->poolOut.push(c.getFd()), false);
	if (!_constantTimeCheck(nextToken, channel.getPass()))
		return (this->handleErrPasswdMismatch(c), this->poolOut.push(c.getFd()), false);

	usedToken.append(1, ' ').append(nextToken);
	channel.setPass("");
	channel.delMode(CHANNEL_KEY);
	return (true);
}

bool	Server::_tCaseAdd(Client &c, Channel &channel, AccessType userAccessOnChannel)
{
    const std::string targetName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_HALFOP)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
	channel.addMode(CHANNEL_TOPIC_PROTECTION);
	return (true);
}

bool	Server::_tCaseDel(Client &c, Channel &channel, AccessType userAccessOnChannel)
{
	const std::string targetName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_HALFOP)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
	channel.delMode(CHANNEL_TOPIC_PROTECTION);
	return (true);
}

bool	Server::_nCaseAdd(Client &c, Channel &channel, AccessType userAccessOnChannel)
{
	const std::string targetName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_HALFOP)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
	channel.addMode(CHANNEL_NOT_EXTERNAL);
	return (true);
}

bool	Server::_nCaseDel(Client &c, Channel &channel, AccessType userAccessOnChannel)
{
	const std::string targetName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_HALFOP)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
	channel.delMode(CHANNEL_NOT_EXTERNAL);
	return (true);
}

bool	Server::_mCaseAdd(Client &c, Channel &channel, AccessType userAccessOnChannel)
{
	const std::string targetName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_HALFOP)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
	channel.addMode(CHANNEL_MODERATED);
	return (true);
}

bool	Server::_mCaseDel(Client &c, Channel &channel, AccessType userAccessOnChannel)
{
	const std::string targetName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_HALFOP)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
	channel.delMode(CHANNEL_MODERATED);
	return (true);
}

bool	Server::_sCaseAdd(Client &c, Channel &channel, AccessType userAccessOnChannel)
{
	const std::string targetName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_OPERATOR)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
	channel.addMode(CHANNEL_SECRET);
	return (true);
}

bool	Server::_sCaseDel(Client &c, Channel &channel, AccessType userAccessOnChannel)
{
	const std::string targetName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_OPERATOR)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
	channel.delMode(CHANNEL_SECRET);
	return (true);
}

bool	Server::_iCaseAdd(Client &c, Channel &channel, AccessType userAccessOnChannel)
{
	const std::string targetName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_OPERATOR)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
	channel.addMode(CHANNEL_INVITE_ONLY);
	return (true);
}

bool	Server::_iCaseDel(Client &c, Channel &channel, AccessType userAccessOnChannel)
{
	const std::string targetName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_OPERATOR)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
	channel.delMode(CHANNEL_INVITE_ONLY);
	return (true);
}

bool	Server::_aCaseAdd(Client &c, Channel &channel, std::istringstream &iss, AccessType userAccessOnChannel, std::string &usedToken)
{
	const std::string targetName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_FOUNDER)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
	std::string	targetUser;

	if (!(iss >> targetUser))
		return (this->handleErrNeedMoreParams(c, "MODE"), this->poolOut.push(c.getFd()), false);
	int	client;
	try {
		client = this->_clientTrie[targetUser];
	} catch (std::exception &e) {
		return (this->handleErrNoSuchNick(c, targetUser), this->poolOut.push(c.getFd()), false);
	}
	this->_clients[client]->addChannelAccess(targetName, USER_PROTECTED);
	usedToken.append(1, ' ').append(targetUser);
	return (true);
}
bool	Server::_aCaseDel(Client &c, Channel &channel, std::istringstream &iss, AccessType userAccessOnChannel, std::string &usedToken)
{
	const std::string targetName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_FOUNDER)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
	std::string	targetUser;

	if (!(iss >> targetUser))
		return (this->handleErrNeedMoreParams(c, "MODE"), false);
	int client;
	try {
		client = this->_clientTrie[targetUser];
	} catch (std::exception &e) {
		return (this->handleErrNoSuchNick(c, targetUser), false);
	}
	this->_clients[client]->delChannelAccess(targetName, USER_PROTECTED);
	usedToken.append(1, ' ').append(targetUser);
	return (true);
}
bool	Server::_oCaseAdd(Client &c, Channel &channel, std::istringstream &iss, AccessType userAccessOnChannel, std::string &usedToken)
{
	const std::string targetName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_PROTECTED)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
	std::string	targetUser;

	if (!(iss >> targetUser))
		return (this->handleErrNeedMoreParams(c, "MODE"), false);
	int client;
	try {
		client = this->_clientTrie[targetUser];
	} catch (std::exception &e) {
		return (this->handleErrNoSuchNick(c, targetUser), false);
	}
	this->_clients[client]->addChannelAccess(targetName, USER_OPERATOR);
	usedToken.append(1, ' ').append(targetUser);
	return (true);
}
bool	Server::_oCaseDel(Client &c, Channel &channel, std::istringstream &iss, AccessType userAccessOnChannel, std::string &usedToken)
{
	const std::string targetName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_PROTECTED)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
	std::string	targetUser;

	if (!(iss >> targetUser))
		return (this->handleErrNeedMoreParams(c, "MODE"), false);
	int client;
	try {
		client = this->_clientTrie[targetUser];
	} catch (std::exception &e) {
		return (this->handleErrNoSuchNick(c, targetUser), false);
	}
	this->_clients[client]->delChannelAccess(targetName, USER_OPERATOR);
	usedToken.append(1, ' ').append(targetUser);
	return (true);
}
bool	Server::_hCaseAdd(Client &c, Channel &channel, std::istringstream &iss, AccessType userAccessOnChannel, std::string &usedToken)
{
	const std::string targetName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_OPERATOR)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
	std::string	targetUser;

	if (!(iss >> targetUser))
		return (this->handleErrNeedMoreParams(c, "MODE"), false);
	int client;
	try {
		client = this->_clientTrie[targetUser];
	} catch (std::exception &e) {
		return (this->handleErrNoSuchNick(c, targetUser), false);
	}
	this->_clients[client]->addChannelAccess(targetName, USER_HALFOP);
	usedToken.append(1, ' ').append(targetUser);
	return (true);
}
bool	Server::_hCaseDel(Client &c, Channel &channel, std::istringstream &iss, AccessType userAccessOnChannel, std::string &usedToken)
{
	const std::string targetName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_OPERATOR)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
	std::string	targetUser;

	if (!(iss >> targetUser))
		return (this->handleErrNeedMoreParams(c, "MODE"), false);
	int client;
	try {
		client = this->_clientTrie[targetUser];
	} catch (std::exception &e) {
		return (this->handleErrNoSuchNick(c, targetUser), false);
	}
	this->_clients[client]->delChannelAccess(targetName, USER_HALFOP);
	usedToken.append(1, ' ').append(targetUser);
	return (true);
}
bool	Server::_vCaseAdd(Client &c, Channel &channel, std::istringstream &iss, AccessType userAccessOnChannel, std::string &usedToken)
{
	const std::string targetName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_HALFOP)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
	std::string	targetUser;

	if (!(iss >> targetUser))
		return (this->handleErrNeedMoreParams(c, "MODE"), false);
	int client;
	try {
		client = this->_clientTrie[targetUser];
	} catch (std::exception &e) {
		return (this->handleErrNoSuchNick(c, targetUser), false);
	}
	this->_clients[client]->addChannelAccess(targetName, USER_VOICE);
	usedToken.append(1, ' ').append(targetUser);
	return (true);
}
bool	Server::_vCaseDel(Client &c, Channel &channel, std::istringstream &iss, AccessType userAccessOnChannel, std::string &usedToken)
{
	const std::string targetName = channel.getNick();

	if (c.getStatus() < CLIENT_ACCESS_OPERATOR && userAccessOnChannel < USER_HALFOP)
		return (this->handleErrChanOPrivsNeeded(c, targetName), false);
	std::string	targetUser;

	if (!(iss >> targetUser))
		return (this->handleErrNeedMoreParams(c, "MODE"), false);
	int client;
	try {
		client = this->_clientTrie[targetUser];
	} catch (std::exception &e) {
		return (this->handleErrNoSuchNick(c, targetUser), false);
	}
	this->_clients[client]->delChannelAccess(targetName, USER_VOICE);
	usedToken.append(1, ' ').append(targetUser);
	return (true);
}


int		Server::_handleCaseAdd(Client &c, std::string modeType, int *i, Channel &channel, std::istringstream &iss, std::string &message, std::string &usedToken)
{
    const AccessType userAccessOnChannel = c.getChannelAccess(channel.getNick());
	unsigned int returnValue = 0;
    (*i)++;
    while (modeType[*i] && isalpha(modeType[*i]))
    {
		int ret = false;
        switch (modeType[*i])
        {
	    	case 'b':
	    		ret = this->_bCaseAdd(c, channel, iss, userAccessOnChannel, usedToken);
				break ;
            case 'k':
                ret = this->_kCaseAdd(c, channel, iss, userAccessOnChannel, usedToken);
                break ;
            case 'l':
                ret = this->_lCaseAdd(c, channel, iss, userAccessOnChannel, usedToken);
                break ;
	    	case 't':
	    		ret = this->_tCaseAdd(c, channel, userAccessOnChannel);
                break ;
	    	case 'n':
	    		ret = this->_nCaseAdd(c, channel, userAccessOnChannel);
                break ;
	    	case 'm':
	    		ret = this->_mCaseAdd(c, channel, userAccessOnChannel);
                break ;
	    	case 's':
	    		ret = this->_sCaseAdd(c, channel, userAccessOnChannel);
                break ;
	    	case 'i':
	    		ret = this->_iCaseAdd(c, channel, userAccessOnChannel);
                break ;
	    	case 'a':
	    		ret = this->_aCaseAdd(c, channel, iss, userAccessOnChannel, usedToken);
                break ;
	    	case 'o':
	    		ret = this->_oCaseAdd(c, channel, iss, userAccessOnChannel, usedToken);
                break ;
	    	case 'h':
	    		ret = this->_hCaseAdd(c, channel, iss, userAccessOnChannel, usedToken);
                break ;
	    	case 'v':
	    		ret = this->_vCaseAdd(c, channel, iss, userAccessOnChannel, usedToken);
                break ;
        }
		if (ret)
			message.append(1, modeType[*i]);
		returnValue += ret;
        (*i)++;
    }
	return (returnValue);
}
int		Server::_handleCaseDel(Client &c, std::string modeType, int *i, Channel &channel, std::istringstream &iss, std::string &message, std::string &usedToken)
{
    const AccessType userAccessOnChannel = c.getChannelAccess(channel.getNick());
    (*i)++;
	unsigned int returnValue = 0;
    while (modeType[*i] && isalpha(modeType[*i]))
    {
		bool ret = false;
	    switch (modeType[*i])
	    {
	    	case 'b':
	    		ret = this->_bCaseDel(c, channel, iss, userAccessOnChannel, usedToken);
                break ;
	    	case 'k':
	    		ret = this->_kCaseDel(c, channel, iss, userAccessOnChannel, usedToken);
                break ;
	    	case 'l':
	    		ret = this->_lCaseDel(c, channel, userAccessOnChannel);
                break ;
	    	case 't':
	    		ret = this->_tCaseDel(c, channel, userAccessOnChannel);
                break ;
	    	case 'n':
	    		ret = this->_nCaseDel(c, channel, userAccessOnChannel);
                break ;
	    	case 'm':
	    		ret = this->_mCaseDel(c, channel, userAccessOnChannel);
                break ;
	    	case 's':
	    		ret = this->_sCaseDel(c, channel, userAccessOnChannel);
                break ;
	    	case 'i':
	    		ret = this->_iCaseDel(c, channel, userAccessOnChannel);
                break ;
	    	case 'a':
	    		ret = this->_aCaseDel(c, channel, iss, userAccessOnChannel, usedToken);
                break ;
	    	case 'o':
	    		ret = this->_oCaseDel(c, channel, iss, userAccessOnChannel, usedToken);
                break ;
	    	case 'h':
	    		ret = this->_hCaseDel(c, channel, iss, userAccessOnChannel, usedToken);
                break ;
	    	case 'v':
	    		ret = this->_vCaseDel(c, channel, iss, userAccessOnChannel, usedToken);
                break ;
	    }
		if (ret)
			message.append(1, modeType[*i]);
		returnValue += ret;
        (*i)++;
    }
    return (returnValue);
}
