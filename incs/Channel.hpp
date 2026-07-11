#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Trie.hpp"
# include <list>

# include <stdint.h>

/* MODE 
 * +i (Invite-only): Users must be invited to join.
 * +s (Secret): The room stays hidden from /LIST commands and user profiles.
 * +m (Moderated): Only users with operator status (+o) can talk.
 * +n (No external): People outside the channel cannot send messages into it.
 * +t (Topic protection): Only channel operators can change the topic.
 */

enum MODE {
	CHANNEL_INVITE				= 1,
	CHANNEL_SECRET				= 2,
	CHANNEL_MODERATED			= 4,
	CHANNEL_NOT_EXTERNAL		= 8,
	CHANNEL_TOPIC_PROTECTION	= 16
};

class Channel {
	protected:
		std::string			_nick;
		std::string			_topic;
		std::list<size_t>	_clientsFD;
		uint8_t				_mode;
	public:
		Channel();
		Channel(std::string nick, std::string topic);
		~Channel();
};

#endif