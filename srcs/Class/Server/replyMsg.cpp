#include "Server.hpp"

std::string Server::_rplPrefix(std::string code, std::string nickName) const
{
	if (nickName.empty())
		nickName = "*";
	std::string rplMessage(":");
	rplMessage.reserve(this->_host.size() + 5 + nickName.size() + 2);
	rplMessage.append(this->_host).append(1, ' ').append(code).append(1, ' ').append(nickName).append(1, ' ');
	return (rplMessage);
}

void	Server::handleRplWelcome(Client &c)
{
	std::string rplMessage(_rplPrefix("001", c.getNick()));
	std::string middlePrefix(":Welcome the IRC Server of 42 (Made by Simon, Tricaducee and Miniflint) - ");
	const std::string &nickName = c.getNick();
	const std::string &userName = c.getUserName();
	const std::string &hostName = c.getHostName();
	rplMessage.reserve(rplMessage.size() + middlePrefix.size() + nickName.size() + userName.size() + hostName.size() + 5);
	rplMessage.append(middlePrefix).append(nickName).append(1, '!').append(userName).append(1, '@').append(hostName).append("\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleRplYourHost(Client &c)
{
	std::string rplMessage(this->_rplPrefix("002", c.getNick()));
	std::string middlePrefix(":Your host is ");
	const std::string &hostName = this->getIp();
	rplMessage.reserve(rplMessage.size() + middlePrefix.size() + hostName.size() + 2);
	rplMessage.append(middlePrefix).append(hostName).append("\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleRplCreated(Client &c)
{
	std::string rplMessage(this->_rplPrefix("003", c.getNick()));
	std::string middlePrefix(":The server was created at this date: [2026-06-13 14:16 GMT+2]\r\n");
	rplMessage.reserve(rplMessage.size() + middlePrefix.size());
	rplMessage.append(middlePrefix);
	c.addBufferOut(rplMessage);
}
void	Server::handleRplMyinfo(Client &c)
{
	std::string rplMessage(this->_rplPrefix("004", c.getNick()));
	std::string middlePrefix(":Bla bla\r\n");
	rplMessage.reserve(rplMessage.size() + middlePrefix.size());
	rplMessage.append(middlePrefix);
	c.addBufferOut(rplMessage);
}
void	Server::handleRplISupport(Client &c)
{
	std::string rplMessage(this->_rplPrefix("005", c.getNick()));
	std::string chanType("CHANTYPES=");
	chanType.append(this->_channelSpecifiers.channelType);
	std::string chanLen(" CHANNELLEN=");
	{
		std::ostringstream oss;
		oss << this->_channelSpecifiers.channelLen;
		chanLen += oss.str();
	}
	std::string chanMode(" CHANMODES=");
	chanMode.append(this->_channelSpecifiers.channelMode);
	std::string chanPrefix(" PREFIX=");
	chanPrefix.append(this->_channelSpecifiers.channelAuthPrefix);
	std::string nickLen(" NICKLEN=");
	{
		std::ostringstream oss;
		oss << this->_clientSpecifiers.nickLenMax;
		nickLen += oss.str();
	}
	std::string userMode(" UMODE=");
	chanPrefix.append(this->_clientSpecifiers.userMode);
	std::string endComment(" :are supported by this server\r\n");
	rplMessage.append(chanType).append(chanLen).append(chanMode)
		.append(chanPrefix).append(nickLen).append(userMode).append(endComment);
	c.addBufferOut(rplMessage);
}
void	Server::handleRplTracelink(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplTraceconnecting(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplTracehandshake(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplTraceunknown(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplTraceoperator(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplTraceuser(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplTraceserver(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplTraceservice(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplTracenewtype(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplTraceclass(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplTracereconnect(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplStatslinkinfo(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplStatscommands(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplStatscline(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplStatsnline(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplStatsiline(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplStatskline(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplStatsqline(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplStatsyline(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplEndofstats(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplUModeIs(Client &c)
{
	std::string rplMessage(this->_rplPrefix("221", c.getNick()));
	std::string modes("");
	rplMessage.append(":");
	AccessType flag = c.getStatus();
	if (flag & CLIENT_ACCESS_INVISIBLE)
		modes.append("i");
	if (flag & CLIENT_ACCESS_HIDDEN_HOST)
		modes.append("x");
	if (flag & CLIENT_ACCESS_DEAF)
		modes.append("d");
	if (flag & CLIENT_ACCESS_REGISTERED)
		modes.append("R");
	if (flag & CLIENT_ACCESS_WHITELIST)
		modes.append("g");
	if (flag & CLIENT_ACCESS_BOT)
		modes.append("B");
	if (flag & CLIENT_ACCESS_OPERATOR)
		modes.append("o");
	if (flag & CLIENT_ACCESS_ADMIN)
		modes.append("a");
	if (!modes.empty())
		rplMessage.append("+");
	else
		modes.append("User has no particular mode");
	c.addBufferOut(rplMessage.append(modes).append("\r\n"));
}
void	Server::handleRplServiceinfo(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplEndofservices(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplService(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplServlist(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplServlistend(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplStatsvline(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplStatslline(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplStatsuptime(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplStatsoline(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplStatshline(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplStatsping(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplStatsbline(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplStatsdline(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplLuserclient(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplLuserop(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplLuserunknown(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplLuserchannels(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplLuserme(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplAdminme(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplAdminloc1(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplAdminloc2(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplAdminemail(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplTracelog(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplTraceend(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplTryagain(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplNone(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplAway(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplUserhost(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplIson(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplUnaway(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplNowaway(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplWhoisuser(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplWhoisserver(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplWhoisoperator(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplWhowasuser(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplEndOfWho(Client &c, std::string target)
{
	std::string rplMessage(this->_rplPrefix("315", c.getNick()));
	c.addBufferOut(rplMessage.append(target).append(" :End of WHO list\r\n"));
}
void	Server::handleRplWhoischanop(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplWhoisidle(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplEndofwhois(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplWhoischannels(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplListStart(Client &c)
{
	std::string rplMessage(this->_rplPrefix("321", c.getNick()));
	rplMessage.append("\r\n");
	// std::cout << rplMessage << std::endl;
	c.addBufferOut(rplMessage);
}
void	Server::handleRplList(Client &c)
{
	std::list<Channel>::const_iterator end = this->_channel.end();
	for (std::list<Channel>::const_iterator it = this->_channel.begin(); it != end; it++)
	{
		Channel currentChannel = *it;
		if ((*it).getMode() & CHANNEL_SECRET && c.getStatus() < CLIENT_ACCESS_OPERATOR && !c.getChannel().isIn(currentChannel.getNick()))
			continue ;
		std::ostringstream amountUserStr;
		std::string rplMessage(this->_rplPrefix("322", c.getNick()));
		amountUserStr << currentChannel.getClientsFD().size();
		std::string channelTopic = currentChannel.getTopic().size() > 2 ? currentChannel.getTopic() : "No topic";
		rplMessage.append(currentChannel.getNick()).append(1, ' ')
			.append(amountUserStr.str()).append(" :").append(channelTopic).append("\r\n");
		c.addBufferOut(rplMessage);
	}
}

void	Server::handleRplListEnd(Client &c)
{
	std::string rplMessage(this->_rplPrefix("323", c.getNick()));
	rplMessage.append(":End of LIST\r\n");
	// std::cout << rplMessage << std::endl;
	c.addBufferOut(rplMessage);
}
void	Server::handleRplChannelModeIs(Client &c, Channel &channel)
{
	std::string rplMessage(this->_rplPrefix("324", c.getNick()));
	rplMessage.append(channel.getNick());
	std::vector<std::string>	args;
	std::string modes("");
	AccessType flag = channel.getMode();
	if (flag & CHANNEL_INVITE_ONLY)
		modes.append("i");
	if (flag & CHANNEL_SECRET)
		modes.append("s");
	if (flag & CHANNEL_MODERATED)
		modes.append("m");
	if (flag & CHANNEL_NOT_EXTERNAL)
		modes.append("n");
	if (flag & CHANNEL_TOPIC_PROTECTION)
		modes.append("t");
	if (flag & CHANNEL_KEY)
	{
		modes.append("k");
		args.push_back(channel.getPass());
	}
	if (flag & CHANNEL_LIMIT_USER)
	{
		std::ostringstream oss;
		modes.append("l");
		if (oss << channel.getMaxUsers())
			args.push_back(oss.str());
	}
	rplMessage.append(" +");
	rplMessage.append(modes);
	std::vector<std::string>::iterator end = args.end();
	for (std::vector<std::string>::iterator it = args.begin(); it != end; it++) {
		if (!((*it).empty()))
			rplMessage.append(1, ' ').append(*it);
	};
	c.addBufferOut(rplMessage.append("\r\n"));
}
void	Server::handleRplUniqopis(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplNoTopic(Client &c, std::string channelName)
{
	std::string rplMessage(this->_rplPrefix("331", c.getNick()));
	rplMessage.append(channelName).append(" :No topic is set").append("\r\n");
	c.addBufferOut(rplMessage);
}
//WILL BE USED
void	Server::handleRplTopic(Client &c, std::string channelName, std::string topic)
{
	std::string rplMessage(this->_rplPrefix("332", c.getNick()));
	rplMessage.append(channelName).append(" :").append(topic).append("\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleRplInviting(Client &c, std::string &targetNick, std::string channelName, bool isInvited)
{
	if (!isInvited)
	{
		std::string rplMessage(this->_rplPrefix("341", c.getNick()));
		rplMessage.append(targetNick).append(1, ' ').append(channelName).append("\r\n");
		c.addBufferOut(rplMessage);
	} else {
		std::string rplMessage(this->_rplPrefix("341", targetNick));
		rplMessage.append(c.getNick()).append(1, ' ').append(channelName).append("\r\n");
		c.addBufferOut(rplMessage);
	}
}
void	Server::handleRplSummoning(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
/* TO DO. too tired - check handler.cpp */
void	Server::handleRplInvitelist(Client &c, std::string channelName)
{
	std::string rplMessage(this->_rplPrefix("336", c.getNick()));
	rplMessage.append(channelName).append(" :Start of invite list\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleRplEndofinvitelist(Client &c, std::string channelName)
{
	std::string rplMessage(this->_rplPrefix("337", c.getNick()));
	rplMessage.append(channelName).append(" :End of invite list\r\n");
	c.addBufferOut(rplMessage);
}
/* TO DO. too tired - check handler.cpp */
void	Server::handleRplExceptlist(Client &c, std::string channelName)
{
	std::string rplMessage(this->_rplPrefix("348", c.getNick()));
	rplMessage.append(channelName).append(" :Start of Except list\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleRplEndofexceptlist(Client &c, std::string channelName)
{
	std::string rplMessage(this->_rplPrefix("349", c.getNick()));
	rplMessage.append(channelName).append(" :End of Except list\r\n");
	c.addBufferOut(rplMessage);
}

void	Server::handleRplVersion(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}

void	Server::handleRplWhoReply(Client &c, Client &cWho, Channel &chan)
{
	std::string rplMessage(this->_rplPrefix("352", c.getNick()));
	std::string	status;
	AccessType	usrStatus = cWho.getStatus();
	if (usrStatus & CLIENT_ACCESS_AWAY)
		status = " G";
	else
		status = " H";
	if (usrStatus & (CLIENT_ACCESS_ADMIN | CLIENT_ACCESS_OPERATOR))
		status.append(1, '*');
	if (usrStatus & CLIENT_ACCESS_BOT)
		status.append(1, 'B');
	AccessType	access = cWho.getChannelAccess(chan.getNick());
	if (access & USER_FOUNDER)
		status.append(1, '~');
	else if (access & USER_PROTECTED)
		status.append(1, '&');
	else if (access & USER_OPERATOR)
		status.append(1, '@');
	else if (access & USER_HALFOP)
		status.append(1, '%');
	else if (access & USER_VOICE)
		status.append(1, '+');
	c.addBufferOut(rplMessage.append(chan.getNick()).append(1, ' ').append(cWho.getUserName()).append(1, ' ').append(cWho.getHostName()).append(1, ' ').append(SERV_HOST_NAME).append(1, ' ').append(cWho.getNick()).append(status).append(" :0 ").append(cWho.getRealName()).append("\r\n"));
}

void	Server::handleRplNameReply(Client &c, std::string channelName, Channel &chan)
{
	std::string rplMessage(this->_rplPrefix("353", c.getNick()));
	if (chan.getMode() & CHANNEL_SECRET)
		rplMessage.append("@ ");
	else
		rplMessage.append("= ");
	rplMessage.append(channelName);
	rplMessage.append(" :");
	std::string	actualReply(rplMessage);
	for (std::vector<int>::iterator it = chan.getClientsFD().begin(); it != chan.getClientsFD().end(); ++it) {
		Client  &itClient = this->getClient(*it);
		AccessType  access = itClient.getChannelAccess(channelName);
		std::string	user;
		if (access & USER_FOUNDER)
			user.append(1, '~');
		else if (access & USER_PROTECTED)
			user.append(1, '&');
		else if (access & USER_OPERATOR)
			user.append(1, '@');
		else if (access & USER_HALFOP)
			user.append(1, '%');
		else if (access & USER_VOICE)
			user.append(1, '+');
		user.append(itClient.getNick());
		if (user.size() + actualReply.size() > MAX_PACKET_SIZE - 2) {
			actualReply.resize(actualReply.size() - 1);
			c.addBufferOut(actualReply.append("\r\n"));
			actualReply = rplMessage;
		}
		actualReply.append(user).append(1, ' ');
	}
	actualReply.resize(actualReply.size() - 1);
	c.addBufferOut(actualReply.append("\r\n"));
}
void	Server::handleRplKilldone(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplClosing(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplCloseend(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplLinks(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplEndoflinks(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplEndofnames(Client &c, std::string channelName)
{
	std::string rplMessage(this->_rplPrefix("366", c.getNick()));
	c.addBufferOut(rplMessage.append(channelName).append(" :End of /NAMES list\r\n"));
}
void	Server::handleRplBanList(Client &c, Channel &channel)
{
	const std::map<int, AccessType>	exceptionList = channel.getClientException();

	std::map<int, AccessType>::const_iterator end = exceptionList.end();
	for (std::map<int, AccessType>::const_iterator it = exceptionList.begin(); it != end; it++) {
		if ((*it).second & EXCEPTION_BANNED)
		{
			std::string rplMessage(this->_rplPrefix("367", c.getNick()));
			rplMessage.append(channel.getNick()).append(1, ' ').append((this->_clients[it->first])->getNick());
			rplMessage.append("!*@*\r\n");
			c.addBufferOut(rplMessage);
		}
	}
}
void	Server::handleRplEndofbanlist(Client &c, std::string channelName)
{
	std::string rplMessage(this->_rplPrefix("368", c.getNick()));
	rplMessage.append(channelName).append(" :End of Channel Ban List\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleRplEndofwhowas(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplInfo(Client &c, std::string message)
{
	std::string rplMessage(this->_rplPrefix("371", c.getNick()));
	c.addBufferOut(rplMessage.append(1, ':').append(message));
}
void	Server::handleRplMotd(Client &c)
{
	std::vector<std::string>::const_iterator end = this->_motd.announcements.end();
	for (std::vector<std::string>::const_iterator it = this->_motd.announcements.begin(); it != end; it++) {
		std::string rplMessage(this->_rplPrefix("372", c.getNick()));
		rplMessage.append(":-").append(*it).append("\r\n");
		c.addBufferOut(rplMessage);
	}
}
void	Server::handleRplInfostart(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplEndofinfo(Client &c)
{
	std::string rplMessage(this->_rplPrefix("374", c.getNick()));
	c.addBufferOut(rplMessage.append(" :End of INFO list"));
}
void	Server::handleRplMotdstart(Client &c)
{
	std::string rplMessage(this->_rplPrefix("375", c.getNick()));
	rplMessage.append(":-").append(this->_motd.motd).append("\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleRplEndofmotd(Client &c)
{
	std::string rplMessage(this->_rplPrefix("376", c.getNick()));
	rplMessage.append(":End of /MOTD\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleRplYoureOper(Client &c, std::string message)
{
	std::string rplMessage(this->_rplPrefix("381", c.getNick()));
	c.addBufferOut(rplMessage.append(1, ':').append(message).append("\r\n"));
}
void	Server::handleRplRehashing(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplYoureservice(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplMyportis(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplTime(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplUsersstart(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplUsers(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplEndofusers(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleRplNousers(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNoSuchNick(Client &c, std::string clientName)
{
	std::string rplMessage(this->_rplPrefix("401", c.getNick()));
	rplMessage.append(clientName).append(" :No such nickname\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNosuchserver(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNoSuchChannel(Client &c, std::string channelName)
{
	std::string rplMessage(this->_rplPrefix("403", c.getNick()));
	rplMessage.append(channelName).append(" :No such channel\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleErrCannotSendToChan(Client &c, std::string channelName)
{
	std::string rplMessage(this->_rplPrefix("404", c.getNick()));
	rplMessage.append(channelName).append(" :Cannot send to Channel/User\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleErrToomanychannels(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrWasnosuchnick(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrToomanytargets(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNosuchservice(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNoorigin(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNoRecipient(Client &c, std::string cmd)
{
	std::string rplMessage(this->_rplPrefix("411", c.getNick()));
	std::string middlePrefix("No Recipient Given (");
	rplMessage.append(middlePrefix).append(cmd).append(")\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNoTextToSend(Client &c)
{
	std::string rplMessage(this->_rplPrefix("412", c.getNick()));
	rplMessage.append(":No text to send or Message in wrong format\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNotoplevel(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrWildtoplevel(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrBadmask(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrUnknowncommand(Client &c, std::string cmd)
{
	std::string rplMessage(this->_rplPrefix("421", c.getNick()));
	rplMessage.append(cmd).append(" :Unknown command\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNomotd(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNoadmininfo(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrFileerror(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNoNicknameGiven(Client &c)
{
	std::string rplMessage(this->_rplPrefix("431", c.getNick()));
	std::string middlePrefix(":No nickname given\r\n");
	rplMessage.reserve(rplMessage.size() + middlePrefix.size());
	rplMessage.append(middlePrefix);
	c.addBufferOut(rplMessage);
}
void	Server::handleErrErroneousNickname(Client &c, std::string targetNickName)
{
	std::string rplMessage(this->_rplPrefix("432", c.getNick()));
	std::string middlePrefix(" :Is erroneous\r\n");
	rplMessage.reserve(rplMessage.size() + targetNickName.size() + middlePrefix.size());
	rplMessage.append(targetNickName).append(1, ' ').append(middlePrefix);
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNicknameInUse(Client &c, std::string targetNickName)
{
	std::string rplMessage(this->_rplPrefix("433", c.getNick()));
	std::string middlePrefix(":Nickname already in use\r\n");
	rplMessage.reserve(rplMessage.size() + targetNickName.size() + middlePrefix.size());
	rplMessage.append(targetNickName).append(1, ' ').append(middlePrefix);
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNickCollision(Client &c, std::string targetNickName)
{
	std::string rplMessage(this->_rplPrefix("436", c.getNick()));
	std::string middlePrefix(" :Nickname collision. Cannot proceed further");
	rplMessage.reserve(rplMessage.size() + (targetNickName.size() * 2) + middlePrefix.size() + 7);
	rplMessage.append(targetNickName).append(middlePrefix).append(" [").append(targetNickName).append("]\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleErrUnavailresource(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrUsernotinchannel(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNotOnChannel(Client &c, std::string channelName)
{
	std::string rplMessage(this->_rplPrefix("442", c.getNick()));
	rplMessage.append(channelName).append(" :You're not on that channel\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleErrUseronchannel(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNologin(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrSummondisabled(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrUsersdisabled(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNotregistered(Client &c)
{
	std::string rplMessage(this->_rplPrefix("451", c.getNick()));
	rplMessage.append(":You have not registered\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNeedMoreParams(Client &c, std::string cmd)
{
	std::string rplMessage(this->_rplPrefix("461", c.getNick()));
	rplMessage.append(cmd).append(" :Not enough parameters\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleErrAlreadyRegistered(Client &c)
{
	std::string rplMessage(this->_rplPrefix("462", c.getNick()));
	std::string middlePrefix(":You may not reregister\r\n");
	rplMessage.reserve(rplMessage.size() + middlePrefix.size());
	rplMessage.append(middlePrefix);
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNopermforhost(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrPasswdMismatch(Client &c)
{
	std::string rplMessage(this->_rplPrefix("464", c.getNick()));
	std::string middlePrefix(":Password mismatch\r\n");
	rplMessage.reserve(rplMessage.size() + middlePrefix.size());
	rplMessage.append(middlePrefix);
	c.addBufferOut(rplMessage);
}
void	Server::handleErrYourebannedcreep(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrYouwillbebanned(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrKeyset(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrChannelisfull(Client &c, std::string channelName)
{
	std::string rplMessage(this->_rplPrefix("471", c.getNick()));
	rplMessage.append(channelName).append(" :Cannot join channel (+l)\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleErrUnknownmode(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrInviteOnlyChan(Client &c, std::string channelName)
{
	std::string rplMessage(this->_rplPrefix("473", c.getNick()));
	rplMessage.append(channelName).append(" :Cannot join channel (+i)\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleErrBannedFromChan(Client &c, std::string channelName)
{
	// "<client> <channel> :Cannot join channel (+b)"
	std::string rplMessage(this->_rplPrefix("474", c.getNick()));
	rplMessage.append(channelName).append(" :Cannot join channel (+b)\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleErrBadChannelKey(Client &c, std::string channelName)
{
	std::string rplMessage(this->_rplPrefix("475", c.getNick()));
	rplMessage.append(channelName).append(" :Cannot join channel (+k)\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleErrBadChanMask(Client &c, std::string channelName)
{
	std::string rplMessage(this->_rplPrefix("476", c.getNick()));
	std::string middlePrefix(" :Bad Channel Mask\r\n");
	rplMessage.append(channelName).append(middlePrefix);
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNochanmodes(Client &c, std::string channelName)
{
	(void)channelName;
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrBanlistfull(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNoPrivileges(Client &c)
{
	std::string rplMessage(this->_rplPrefix("481", c.getNick()));
	rplMessage.append(":Permission Denied- You're not an IRC operator or Administrator\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleErrBadChanName(Client &c, std::string channelName)
{
	std::string rplMessage(this->_rplPrefix("479", c.getNick()));
	std::string middlePrefix(" :Illegal channel name\r\n");
	rplMessage.append(channelName).append(middlePrefix);
	c.addBufferOut(rplMessage);
}
void	Server::handleErrChanOPrivsNeeded(Client &c, std::string channelName)
{
	std::string rplMessage(this->_rplPrefix("482", c.getNick()));
	rplMessage.append(channelName).append(" :Insufficient rights to do this command\r\n");
	c.addBufferOut(rplMessage);
}
void	Server::handleErrCantkillserver(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrRestricted(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrUniqoprivsneeded(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNooperhost(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrNoservicehost(Client &c)
{
	std::string rplMessage(this->_rplPrefix("000", c.getNick()));
	c.addBufferOut(rplMessage);
}
void	Server::handleErrUmodeunknownflag(Client &c)
{
	std::string rplMessage(this->_rplPrefix("501", c.getNick()));
	c.addBufferOut(rplMessage.append(":Unknown MODE flag\r\n"));
}
void	Server::handleErrUsersDontMatch(Client &c)
{
	std::string rplMessage(this->_rplPrefix("502", c.getNick()));
	rplMessage.append(":Can't view mode for other users\r\n");
	c.addBufferOut(rplMessage);
}
