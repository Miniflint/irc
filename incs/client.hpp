#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "trie.hpp"

class Client {
	protected:
		unsigned int	_fd;
		std::string		_nick;
	public:
		Client();
		Client(unsigned int socket, std::string &nick);
		~Client();
};

#endif