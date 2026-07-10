#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "trie.hpp"
# include "Client.hpp"

class Channel {
	protected:
		std::string			_nick;
		std::string			_topic;
		std::list<Client>	_clients;
	public:
		Channel();
		Channel(std::string nick, std::string topic);
		~Channel();
};

#endif