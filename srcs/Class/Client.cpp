#include "Client.hpp"
#include "main.hpp"

Client::Client() {}

Client::Client(int socket, std::string host, int port) : _fd(socket), _nick(""), _userName(""), _hostName(host), _serverName(""), _realName(""), _port(port), _avertissements(0), _userStatus(USR_STATUS_NONE), buffer(""), quitRequest(CLIENT_QUIT_NONE), flagsLogin(FLAG_CLIENT_NONE) {}

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
	const size_t index = bufferOut.find("\r\n");
	if (index >= MAX_PACKET_SIZE - 2)
	{
		bufferOut.resize(MAX_PACKET_SIZE - 2);
		bufferOut.append("\r\n");
	}
	this->_bufferOut = bufferOut;
}

void		Client::addBufferOut(std::string bufferOut)
{
	const size_t index = bufferOut.find("\r\n");
	if (index == std::string::npos)
		return ;
	if (index >= MAX_PACKET_SIZE - 2)
	{
		bufferOut.resize(MAX_PACKET_SIZE - 2);
		bufferOut.append("\r\n");
	}
	serverSendsLog(bufferOut);
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

void	Client::addChannelAccess(const std::string &toCheck, AccessType flag)
{
	try {
		this->_channel[toCheck].second |= flag;
	} catch (std::exception &e) { (void)e; }
}

void	Client::delChannelAccess(const std::string &toCheck, AccessType flag) const
{
	try {
		this->_channel[toCheck].second &= ~flag;
	} catch (std::exception &e) { (void)e; }
}

bool	Client::checkChannelAccess(const std::string &toCheck, AccessType mode) const
{
	try {
		return ((this->_channel[toCheck].second & mode) == mode);
	} catch (std::exception &e) { (void)e; }
	return (false);
}

AccessType	Client::getChannelAccess(const std::string &toCheck) const
{
	try {
		return (this->_channel[toCheck].second);
	} catch (std::exception &e) { (void)e; }
	return (NO_ACCESS);
}

void	Client::addStatus(uint8_t status)
{
	this->_userStatus |= status;
}

void	Client::delStatus(uint8_t status)
{
	this->_userStatus &= ~status;
}

bool	Client::checkStatus(uint8_t status) const
{
	return ((this->_userStatus & status) == status);
}

uint8_t	Client::getStatus() const
{
	return (this->_userStatus);
}

Trie<std::pair<Channel *, AccessType> >	&Client::getChannel(void)
{
	return (this->_channel);
}
