#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "trie.hpp"

class Client {
	protected:
		std::size_t		_fd;
		std::string		_nick;
	public:
		Client();
		Client(std::size_t socket);
		void		set_nick(std::string nick);
		~Client();
};

#endif