#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "trie.hpp"
# include "Channel.hpp"
# define ACCESS_ADM 0x4
# define ACCESS_OPR 0x2
# define ACCESS_USR 0x1

typedef uint8_t AccessType;

class Client {
	protected:
		size_t			_fd;
		std::string		_nick;
		std::string		_user;
		Trie<std::pair<Channel *, AccessType>>	_channel;
	public:
		Client();
		Client(std::size_t socket);
		void		set_nick(std::string nick);
		~Client();
};

#endif