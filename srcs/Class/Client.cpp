#include "Client.hpp"

Client::Client() : _fd(0), _avertissements(0) {}

Client::Client(size_t socket) : _fd(socket), _avertissements(0) {}
Client::Client(size_t socket, std::string nickName) : _fd(socket), _nick(nickName), _avertissements(0) {}
Client::Client(size_t socket, std::string nickName, std::string hostName) : _fd(socket), _nick(nickName), _hostName(hostName), _avertissements(0) {}

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

void	Client::setFd(size_t fd)
{
	this->_fd = fd;
}

size_t	Client::getFd() const
{
	return (this->_fd);
}