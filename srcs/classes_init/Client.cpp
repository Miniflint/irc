#include "Client.hpp"

Client::Client() : _fd(0), _avertissements(0) {}

Client::Client(size_t socket) : _fd(socket), _avertissements(0) {}
Client::Client(size_t socket, std::string nick) : _fd(socket), _nick(nick), _user(nick), _avertissements(0) {}

Client::~Client() {}

void		Client::set_nick(std::string nick)
{
	this->_nick = nick;
}
#include <iostream>
void		Client::set_warning(int warn_lvl)
{
	this->_avertissements = warn_lvl;
}

int		Client::get_warning() const
{
	return (this->_avertissements);
}