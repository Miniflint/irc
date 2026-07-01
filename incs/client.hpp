#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "trie.hpp"

class Client {
	protected:
		unsigned long	_fd;
		std::string		_nick;
	public:
		Client();
		Client(unsigned long socket);
		Client(std::size_t socket);
		void		set_nick(std::string nick);
		~Client();
};

#endif