#include "client.hpp"

Client::Client()
{
	this->_fd = 0;
}

Client::Client(std::size_t socket) : _fd(socket)
{

}

Client::~Client()
{

}

void		Client::set_nick(std::string nick)
{
	this->_nick = nick;
}