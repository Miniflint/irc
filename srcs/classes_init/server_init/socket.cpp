#include "Server.hpp"

bool	Server::_sockServerInit() {
	return ((this->_sockServerFD = socket(SOCK_DOMAIN, SOCK_STREAM | SOCK_NONBLOCK, 0)) != -1);
}

bool        Server::_clientAdd()
{
	struct sockaddr	addr;
	socklen_t		addrLen;
    accept(this->_sockServerFD, &addr, &addrLen);
}
