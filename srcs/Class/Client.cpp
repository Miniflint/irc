#include "Client.hpp"

Client::Client() {}

Client::Client(int socket, std::string host, int port) : _fd(socket), _nick(""), _userName(""), _hostName(""), _serverName(""), _realName(""), _host(host), _port(port), _avertissements(0), buffer(""), quitRequest(CLIENT_QUIT_NONE) {}

Client::~Client() {}

void		Client::setNick(std::string nick)
{
	this->_nick = nick;
}

const std::string	&Client::getNick() const
{
	return (this->_nick);
}

void		Client::setUserName(std::string userName)
{
	this->_userName = userName;
}

const std::string	&Client::getUserName() const
{
	return (this->_userName);
}

void		Client::setWarning(int warn_lvl)
{
	this->_avertissements = warn_lvl;
}

int		Client::getWarning() const
{
	return (this->_avertissements);
}

void		Client::setHostName(std::string hostName)
{
	this->_hostName = hostName;
}

const std::string	&Client::getHostName() const
{
	return (this->_hostName);
}

void		Client::setServerName(std::string serverName)
{
	this->_serverName = serverName;
}

const std::string	&Client::getServerName() const
{
	return (this->_serverName);
}

void		Client::setRealName(std::string realName)
{
	this->_realName = realName;
}

const std::string	&Client::getRealName() const
{
	return (this->_realName);
}

void		Client::setBufferOut(std::string bufferOut)
{
	this->_bufferOut = bufferOut;
}

void		Client::addBufferOut(std::string bufferOut)
{
	this->_bufferOut += bufferOut;
}

std::string	&Client::getBufferOut()
{
	return (this->_bufferOut);
}

void		Client::setBufferQuit(std::string bufferQuit)
{
	this->_bufferQuit = bufferQuit;
}

std::string	&Client::getBufferQuit()
{
	return (this->_bufferQuit);
}

void	Client::setFd(size_t fd)
{
	this->_fd = fd;
}

size_t	Client::getFd() const
{
	return (this->_fd);
}

void	Client::addAccess(const std::string &toCheck, AccessType flag)
{
	this->_channel[toCheck].second |= flag;
}

void	Client::delAccess(const std::string &toCheck, AccessType flag) const
{
	this->_channel[toCheck].second &= ~flag;
}

bool				Client::checkFlag(const std::string &toCheck, AccessType mode) const
{
	return ((this->_channel[toCheck].second & mode) == mode);
}

const Trie<std::pair<Channel *, AccessType> >	&Client::getChannel(void) const
{
	return (this->_channel);
}
