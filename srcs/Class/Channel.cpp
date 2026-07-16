#include "Channel.hpp"

Channel::Channel() : _nick("general"), _topic("general"), _password(""), _maxUsers(-1), _mode(NO_ACCESS) {}

Channel::Channel(std::string nick, std::string pass) : _nick(nick), _topic(""), _password(pass), _maxUsers(-1), _mode(NO_ACCESS) {}

Channel::Channel(const Channel &src) : _nick(src.getNick()), _topic(src.getTopic()), _password(src.getPass()), _maxUsers(src.getMaxUsers()), _clientsFD(src.getClientsFD()), _mode(src.getMode()) {}

Channel::~Channel() {}

Channel	&Channel::operator=(const Channel &src) {
	this->_nick = src.getNick();
	this->_topic = src.getTopic();
	this->_password = src.getPass();
	this->_maxUsers = src.getMaxUsers();
	this->_clientsFD = src.getClientsFD();
	this->_mode = src.getMode();
	return (*this);
}

std::string			Channel::getNick(void) const
{
	return (this->_nick);
}

void				Channel::setNick(std::string nick)
{
	this->_nick = nick;
}

std::string			Channel::getTopic(void) const
{
	return (this->_topic);
}

void				Channel::setTopic(std::string topic)
{
	this->_topic = topic;
}

std::string			Channel::getPass(void) const
{
	return (this->_password);
}

void				Channel::setPass(std::string pass)
{
	this->_password = pass;
}

std::vector<int>	Channel::getClientsFD(void) const
{
	return (this->_clientsFD);
}

std::vector<int>	&Channel::getClientsFD(void)
{
	return (this->_clientsFD);
}

void				Channel::addClientsFD(int fd)
{
	this->_clientsFD.push_back(fd);
}

AccessType	Channel::getMode(void) const
{
	return (this->_mode);
}

bool	Channel::checkMode(AccessType mode) const
{
	return ((this->_mode & mode) == mode);
}

void	Channel::setMode(AccessType mode)
{
	this->_mode = mode;
}

void	Channel::addMode(AccessType mode)
{
	this->_mode |= mode;
}

void	Channel::delMode(AccessType mode)
{
	this->_mode &= ~mode;
}

int		Channel::getMaxUsers(void) const {
	return (this->_maxUsers);
}
void	Channel::setMaxUsers(int limit) {
	this->_maxUsers = limit;
}

AccessType			Channel::getAccessClient(int fd)
{
	std::map<int, AccessType>::iterator it = this->_exceptionList.find(fd);
	if (it == this->_exceptionList.end())
		return (NO_ACCESS);
	return (it->second);
}

void				Channel::addClientException(int fd, AccessType flag)
{
	std::map<int, AccessType>::iterator it = this->_exceptionList.find(fd);
	if (it == this->_exceptionList.end())
		this->_exceptionList[fd] = flag;
	it->second |= flag;
}
void				Channel::delClientException(int fd, AccessType flag)
{
	std::map<int, AccessType>::iterator it = this->_exceptionList.find(fd);
	if (it == this->_exceptionList.end())
		return ;
	it->second &= ~flag;
	if (it->second == NO_ACCESS)
		this->_exceptionList.erase(it);
}
