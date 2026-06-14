#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "main.hpp"

class Client {
	protected:
		std::string		_nick;
		std::string		_about;
		unsigned int	_fd;
	public:
		Client(unsigned int socket);
		~Client();
};

#endif