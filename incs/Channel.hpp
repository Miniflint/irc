#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Trie.hpp"
# include <list>

# include <stdint.h>
# include <map>

// ajouter l et k
// k
/* MODE 
 * +i (Invite-only): Users must be invited to join.
 * +s (Secret): The room stays hidden from /LIST commands and user profiles.
 * +m (Moderated): Only users with voice (+v) or operator status (+o) can talk.
 * +n (No external): People outside the channel cannot send messages into it.
 * +t (Topic protection): Only channel operators can change the topic.
 * +k (Key): Set or remove a channel password
 */

typedef uint16_t AccessType;

const AccessType NO_ACCESS					= 0x0;

/* differents access possible de user sur un channel */
const AccessType USER_FOUNDER				= 0x10;	// (~)q
const AccessType USER_PROTECTED				= 0x8;	// (&)a
const AccessType USER_OPERATOR				= 0x4;	// (@)o
const AccessType USER_HALFOP				= 0x2;	// (%)h
const AccessType USER_VOICE					= 0x1;	// (+)v

/* different mode de channel possible */
const AccessType CHANNEL_INVITE_ONLY		= 0x1;	 // i
const AccessType CHANNEL_SECRET 			= 0x2;	 // s | à prendre en compte
const AccessType CHANNEL_MODERATED 			= 0x4;	 // m
const AccessType CHANNEL_NOT_EXTERNAL		= 0x8;	 // n
const AccessType CHANNEL_TOPIC_PROTECTION	= 0x10;	 // t | a prendre en compte
const AccessType CHANNEL_KEY				= 0x20;  // k
const AccessType CHANNEL_LIMIT_USER			= 0x40;  // l
const AccessType CHANNEL_BAN				= 0x80;  // b | a terminer

/* Liste d'exception sur les channels | qui est invité / qui est ban */
const AccessType EXCEPTION_INVITED			= 0x1;
const AccessType EXCEPTION_BANNED			= 0x2;

class Channel {
	protected:
		std::string						_nick;
		std::string						_topic;
		std::string						_password;
		int								_maxUsers;
		std::vector<int>				_clientsFD;
		std::map<int, AccessType>		_exceptionList;
		AccessType						_mode;
	public:
		Channel();
		Channel(std::string nick, std::string pass);
		Channel(const Channel &src);
		~Channel();
		Channel	&operator=(const Channel &src);
		std::string						getNick(void) const;
		void							setNick(std::string nick);
		std::string						getTopic(void) const;
		void							setTopic(std::string topic);
		std::string						getPass(void) const;
		void							setPass(std::string pass);
		int								getMaxUsers(void) const;
		void							setMaxUsers(int limit);
		std::vector<int>				getClientsFD(void) const;
		std::vector<int>				&getClientsFD(void);
		void							addClientsFD(int fd);
		AccessType						getAccessClient(int fd);
		void							addClientException(int fd, AccessType flag);
		void							delClientException(int fd, AccessType flag);
		const std::map<int, AccessType>	&getClientException() const;
		AccessType						getMode(void) const;
		bool							checkMode(AccessType mode) const;
		void							setMode(AccessType mode);
		void							addMode(AccessType mode);
		void							delMode(AccessType mode);
};

// addMode(CHANNEL_INVITE)
// addMode(~CHANNEL_INVITE)

#endif
