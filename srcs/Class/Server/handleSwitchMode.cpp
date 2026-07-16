#include "Server.hpp"

bool					Server::_lCasePlus(Client &c, Channel &channel, std::istringstream &iss, AccessType userAccessOnChannel)
{
    const std::string targetName = channel.getNick();

	if (userAccessOnChannel < USER_HALFOP)
		return (this->handleErrChanOPrivsNeeded(c, targetName), true);
	int r;
	iss >> r;
	if (iss.fail())
		return (this->handleErrNeedMoreParams(c, "MODE"), this->poolOut.push(c.getFd()), false);

	channel.setMaxUsers(r);
	channel.addMode(CHANNEL_LIMIT_USER);
	std::string		full(_makeHostMask(c, "MODE"));
	std::ostringstream convertToString;
	convertToString << r;
	full.append(targetName).append(" +l ").append(convertToString.str()).append("\r\n");
	this->sendToChannel(channel, full);
    return (true);
}

bool					Server::_lCaseMinus(Client &c, Channel &channel, AccessType userAccessOnChannel)
{
    const std::string targetName = channel.getNick();
 
	if (userAccessOnChannel < USER_HALFOP)
		return (this->handleErrChanOPrivsNeeded(c, targetName), true);

	channel.delMode(CHANNEL_LIMIT_USER);
	std::string		full(_makeHostMask(c, "MODE"));
	full.append(targetName).append(" -l\r\n");
	this->sendToChannel(channel, full);
    return (true);
}

bool					Server::_kCasePlus(Client &c, Channel &channel, std::istringstream &iss, AccessType userAccessOnChannel)
{
    const std::string targetName = channel.getNick();

    if (userAccessOnChannel < USER_HALFOP)
		return (this->handleErrChanOPrivsNeeded(c, targetName), true);
    std::string nextToken;
	if (!(iss >> nextToken))
		return (this->handleErrNeedMoreParams(c, "MODE"), this->poolOut.push(c.getFd()), false);
	if (channel.getMode() & CHANNEL_KEY && !_constantTimeCheck(nextToken, channel.getPass()))
		return (this->handleErrPasswdMismatch(c), this->poolOut.push(c.getFd()), false);

	channel.setPass(nextToken);
	std::string		full(_makeHostMask(c, "MODE"));
	full.append(targetName).append(" +k ").append(nextToken).append("\r\n");
    channel.addMode(CHANNEL_KEY);
	this->sendToChannel(channel, full);
	return (true);
}

bool					Server::_kCaseMinus(Client &c, Channel &channel, std::istringstream &iss, AccessType userAccessOnChannel)
{
    const std::string targetName = channel.getNick();
    if (userAccessOnChannel < USER_HALFOP)
		return (this->handleErrChanOPrivsNeeded(c, targetName), true);
    std::string nextToken;
	if (!(iss >> nextToken))
		return (this->handleErrNeedMoreParams(c, "MODE"), this->poolOut.push(c.getFd()), false);
	if (!_constantTimeCheck(nextToken, channel.getPass()))
		return (this->handleErrPasswdMismatch(c), this->poolOut.push(c.getFd()), false);

	std::string		full(_makeHostMask(c, "MODE"));
	full.append(targetName).append(" -k ").append(nextToken).append("\r\n");
    channel.delMode(CHANNEL_KEY);
	channel.setPass(nextToken);
	this->sendToChannel(channel, full);
	return (true);
}

int						Server::_handleCasePlus(Client &c, std::string modeType, int *i, Channel &channel, std::istringstream &iss)
{
    const AccessType userAccessOnChannel = c.getChannelAccess(channel.getNick());
    (*i)++;
    while (modeType[*i] && isalpha(modeType[*i]))
    {
        switch (modeType[*i])
        {
            case 'l':
                this->_lCasePlus(c, channel, iss, userAccessOnChannel);
                break ;
            case 'k':
                this->_kCasePlus(c, channel, iss, userAccessOnChannel);
                break ;
        }
        (*i)++;
    }
	return (true);
}
int						Server::_handleCaseMinus(Client &c, std::string modeType, int *i, Channel &channel, std::istringstream &iss)
{
    const AccessType userAccessOnChannel = c.getChannelAccess(channel.getNick());
    (*i)++;
    while (modeType[*i] && isalpha(modeType[*i]))
    {
	    switch (modeType[*i])
	    {
	    	case 'l':
	    		this->_lCaseMinus(c, channel, userAccessOnChannel);
                break ;
	    	case 'k':
	    		this->_kCaseMinus(c, channel, iss, userAccessOnChannel);
                break ;
	    }
        (*i)++;
    }
    return (true);
}
