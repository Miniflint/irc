#ifndef SERVER_HPP
# define SERVER_HPP

# include "string"
# include "iostream"

class Server {
	private:
		std::string		_password;
		unsigned int	_pid;
		std::string		_listening_ip;
		std::string		_listening_port;
};

#endif