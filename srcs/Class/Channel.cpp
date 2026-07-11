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