#ifndef SERVER_HPP
# define SERVER_HPP

# include "main.hpp"

class Server {
	private:
		unsigned int		_pid;
		unsigned int		_port;
		std::string			_password;
		std::string			_ip;
		std::list<Client>	_clients;
		std::list<Channel>	_channels;
	public:
		Server(unsigned int pid, std::string password, unsigned int port) : _pid(pid), _password(password), _port(port), _ip(std::string("0.0.0.0")) {};
		~Server();
		void	nick(std::string nick);
		void	user(std::string msg);
		void	privmsg(std::string msg);
};

#endif