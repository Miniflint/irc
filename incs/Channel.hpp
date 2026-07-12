#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Trie.hpp"
# include <list>

# include <stdint.h>

/* MODE 
 * +i (Invite-only): Users must be invited to join.
 * +s (Secret): The room stays hidden from /LIST commands and user profiles.
 * +m (Moderated): Only users with voice (+v) or operator status (+o) can talk.
 * +n (No external): People outside the channel cannot send messages into it.
 * +t (Topic protection): Only channel operators can change the topic.
 */

typedef uint16_t AccessType;

const AccessType CHANNEL_INVITE 			= 0x1;	// i
const AccessType CHANNEL_SECRET 			= 0x2;	// s
const AccessType CHANNEL_MODERATED 			= 0x4;	// m
const AccessType CHANNEL_NOT_EXTERNAL		= 0x8;	// n
const AccessType CHANNEL_TOPIC_PROTECTION	= 0x10;	// t
const AccessType CHANNEL_USER_VOICE			= 0x20; // v
const AccessType CHANNEL_USER_OPERATOR		= 0x40; // o

class Channel {
	protected:
		std::string			_nick;
		std::string			_topic;
		std::vector<size_t>	_clientsFD;
		AccessType				_mode;
	public:
		Channel();
		Channel(std::string nick, std::string topic);
		~Channel();
		std::string			getNick(void) const;
		void				setNick(std::string nick);
		std::string			getTopic(void) const;
		void				setTopic(std::string topic);
		std::vector<size_t>	getClientsFD(void) const;
		void				addClientsFD(size_t fd);

		AccessType			getMode(void) const;
		bool				checkMode(AccessType mode) const;
		void				setMode(AccessType mode);
		void				addMode(AccessType mode);
		void				delMode(AccessType mode);
};

// addMode(CHANNEL_INVITE)
// addMode(~CHANNEL_INVITE)

#endif