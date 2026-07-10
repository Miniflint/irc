#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Trie.hpp"
# include <list>

class Channel {
	protected:
		std::string			_nick;
		std::string			_topic;
		std::list<size_t>	_clientsFD;
	public:
		Channel();
		Channel(std::string nick, std::string topic);
		~Channel();
};

#endif