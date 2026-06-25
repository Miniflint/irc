#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "trie.hpp"
# include "client.hpp"

class Channel {
	protected:
		std::string		_nick;
		std::string		_topic;
		Trie<Client>	_clients;
	public:
		Channel();
		Channel(std::string nick, std::string topic);
		~Channel();
};

#endif