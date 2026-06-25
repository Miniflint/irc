#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "main.hpp"

class Channel {
	protected:
		std::string		_nick;
		std::string		_topic;
		Trie<Client>	_clients;
	public:
		Channel(unsigned int socket);
		~Channel();
};

#endif