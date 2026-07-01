#include "client.hpp"

Client::Client()
{
	this->_fd = 0;
	this->_nick = "dflt";
}

Client::Client(unsigned long socket) : _fd(socket)
{

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