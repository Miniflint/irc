#include "Server.hpp"

// const AccessType CHANNEL_INVITE_ONLY			= 0x1;	 // i
// const AccessType CHANNEL_SECRET 				= 0x2;	 // s
// const AccessType CHANNEL_MODERATED 			= 0x4;	 // m
// const AccessType CHANNEL_NOT_EXTERNAL		= 0x8;	 // n
// const AccessType CHANNEL_TOPIC_PROTECTION	= 0x10;	 // t
// const AccessType CHANNEL_KEY					= 0x20;  // k
// const AccessType CHANNEL_LIMIT_USER			= 0x40;  // l
// const AccessType CHANNEL_USER_VOICE			= 0x80;  // v
// const AccessType CHANNEL_USER_OPERATOR		= 0x100; // o

static inline Channel	*sendRet(Client &c, Server &serv, Channel *chan) {
	serv.poolOut.push(c.getFd());
	return (chan);
}

// bool	Server::delClientToChannel(Client &c, Channel *chan, std::string &channelName) {
// 	std::list<Channel>::iterator end = this->_channel.end();
// 		std::list<Channel>::iterator it = this->_channel.begin();
// 		while (it != end) {
// 			try {
// 				c->getChannel()[it->getNick()];
// 				std::vector<int> &clientFd = it->getClientsFD();
// 				for (std::vector<int>::iterator itB = clientFd.begin(); itB != clientFd.end();) {
// 					Client	&itClient = this->getClient(*itB);
// 					if (*itB == fd) {
// 						itB = clientFd.erase(itB);
// 					} else {
// 						if (!c->getBufferQuit().empty() && itClient.quitRequest == CLIENT_QUIT_NONE)
// 							this->sendToClient(itClient, c->getBufferQuit());
// 						++itB;
// 					}
// 				}
// 				std::vector<int>::iterator rtn = std::find(clientFd.begin(), clientFd.end(), c->getFd());
// 				if (rtn != clientFd.end())
// 					clientFd.erase(rtn);
// 				if (clientFd.empty()) {
// 					std::vector<int>	*
// 					it = this->_channel.erase(it);
// 				} else
// 					++it;
// 			} catch (std::exception &e) {(void)e;}
// 		}
// }

Channel	*Server::_joinChannelSendMsg(Client &c, Channel *chan, std::string &channelName) {
	std::string	joinMsg(this->_makeHostMask(c, "JOIN"));
	joinMsg.append(channelName).append("\r\n");
	for (std::vector<int>::iterator it = chan->getClientsFD().begin(); it != chan->getClientsFD().end(); ++it)
		this->sendToClient(this->getClient(*it), joinMsg);
	this->handleRplTopic(c, channelName, chan->getTopic());
	this->handleRplNameReply(c, channelName, *chan);
	this->handleRplEndofnames(c, channelName);
	return (chan);
}

Channel	*Server::createNewChannel(std::string name, std::string pass) {
	Channel	chan(name, pass);
	if (!pass.empty())
		chan.setMode(CHANNEL_KEY);
	chan.setPass(pass);
	this->_channel.push_front(chan);
	Channel	*retChan = &this->_channel.front();
	this->_channelTrie.add(name, retChan);
	return (retChan);
}

Channel	*Server::addClientToChannel(int fd, std::string channelName, std::string channelPass) {
	Client	&client = this->getClient(fd);
	return (this->addClientToChannel(client, channelName, channelPass));
}

Channel	*Server::addClientToChannel(Client &client, std::string channelName, std::string channelPass) {
	Channel	*chan;
	try {
		chan = this->_channelTrie[channelName];
		try {
			client.getChannel()[channelName];
			return (NULL); //déjà dans le channel
		} catch (std::exception &e) {
			AccessType clientAccess = chan->getAccessClient(client.getFd());
			if ((chan->getMode() & CHANNEL_KEY) && chan->getPass() != channelPass)
				return (this->handleErrBadChannelKey(client, channelName), sendRet(client, *this, reinterpret_cast<Channel *>(NULL))); //mauvais mot de passes
			if ((chan->getMode() & CHANNEL_BAN) && clientAccess & EXCEPTION_BANNED)
				return (this->handleErrBannedFromChan(client, channelName), sendRet(client, *this, reinterpret_cast<Channel *>(NULL))); //client bannis
			if ((chan->getMode() & CHANNEL_INVITE_ONLY) && !(clientAccess & EXCEPTION_INVITED))
				return (this->handleErrInviteOnlyChan(client, channelName), sendRet(client, *this, reinterpret_cast<Channel *>(NULL))); //pas invité
			if ((chan->getMode() & CHANNEL_LIMIT_USER) && chan->getClientsFD().size() >= static_cast<size_t>(chan->getMaxUsers()))
				return (this->handleErrChannelisfull(client, channelName), sendRet(client, *this, reinterpret_cast<Channel *>(NULL))); //plus de place sur le channel
			client.getChannel().add(channelName, std::pair<Channel *, AccessType>(chan, NO_ACCESS));
			chan->addClientsFD(client.getFd());
			return (this->_joinChannelSendMsg(client, chan, channelName));
		}
	} catch (std::exception &e) {
		if (this->_channelSpecifiers.channelType.find(channelName[0]) == std::string::npos)
			return (this->handleErrBadChanMask(client, channelName), sendRet(client, *this, reinterpret_cast<Channel *>(NULL))); //nom de channel invalid
		chan = this->createNewChannel(channelName, channelPass);
		client.getChannel().add(channelName, std::pair<Channel *, AccessType>(chan, USER_OPERATOR | USER_FOUNDER));
		chan->addClientsFD(client.getFd());
		return (this->_joinChannelSendMsg(client, chan, channelName));
	}
	return (NULL);
}

Channel	*Server::addClientToChannel(int fd, std::string channelName) {
	Client	&client = this->getClient(fd);
	return (this->addClientToChannel(client, channelName));
}

Channel	*Server::addClientToChannel(Client &client, std::string channelName) {
	return (this->addClientToChannel(client, channelName, ""));
}
