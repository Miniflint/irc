#include "client.hpp"

Client::Client()
{
	this->_fd = 0;
	this->_nick = "dflt";
}

Client::Client(unsigned int socket, std::string &nick) : _fd(socket), _nick(nick)
{

}

Client::~Client()
{

}