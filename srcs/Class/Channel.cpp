#include "Channel.hpp"

Channel::Channel()
{
	this->_nick = "dfltchan";
	this->_topic = "DEFAULT CHANNEL NO TOPIC";
}

Channel::Channel(std::string nick, std::string topic) : _nick(nick), _topic(topic)
{

}
Channel::~Channel()
{

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

AccessType				Channel::getMode(void) const
{
	return (this->_mode);
}

bool				Channel::checkMode(AccessType mode) const
{
	return ((this->_mode & mode) == mode);
}

void				Channel::setMode(AccessType mode)
{
	this->_mode = mode;
}

void				Channel::addMode(AccessType mode)
{
	this->_mode |= mode;
}

void				Channel::delMode(AccessType mode)
{
	this->_mode &= ~mode;
}
