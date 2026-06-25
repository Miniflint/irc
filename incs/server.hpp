#ifndef SERVER_HPP
# define SERVER_HPP

# include "main.hpp"

class Server {
	private:
		unsigned int		_pid;
		unsigned int		_port;
		std::string			_password;
		std::string			_ip;
		std::list<cmdFn>	_commands;
		std::list<Client *>	_clients;
		std::list<Channel>	_channels;
	public:
		Server(unsigned int port, std::string password);;
		~Server();
		void	nick(std::string nick);
		void	user(std::string msg);
		void	privmsg(std::string msg);
};

#endif