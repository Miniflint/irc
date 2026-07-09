#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "trie.hpp"
# include "Channel.hpp"

class Client {
	protected:
		size_t			_fd;
		std::string		_nick;
		std::string		_user;
		Trie<Channel *>	_channel;
	public:
		Client();
		Client(std::size_t socket);
		void		set_nick(std::string nick);
		~Client();
};

#endif