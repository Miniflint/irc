#include "Client.hpp"

Client::Client() : _fd(0) {}

Client::Client(size_t socket) : _fd(socket), _avertissements(0) {}
Client::Client(size_t socket, std::string nick) : _fd(socket), _nick(nick), _user(nick), _avertissements(0) {}

Client::~Client() {}

void		Client::set_nick(std::string nick)
{
	this->_nick = nick;
	this->_avertissements = 0;
}


void		set_warning(uint8_t warn_lvl)

uint8_t		get_warning() const
{

}