#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Trie.hpp"
# include <stdint.h>
# include "Channel.hpp"
# include <sys/socket.h>

bool	_constantTimeCheck(const std::string &pass, const std::string &toCheck);

# define CLIENT_QUIT_NONE 0x0
# define CLIENT_QUIT_REQUEST 0x1
# define CLIENT_QUIT_ACCEPT 0x2

# ifndef MAX_PACKET_SIZE
#  define MAX_PACKET_SIZE 512U
# endif

const uint8_t FLAG_CLIENT_NONE = 0x0;
const uint8_t FLAG_CLIENT_PASS = 0x1;
const uint8_t FLAG_CLIENT_NICK = 0x2;
const uint8_t FLAG_CLIENT_USER = 0x4;
const uint8_t FLAG_CLIENT_CAPL = 0x8;
const uint8_t FLAG_CLIENT_FULL = FLAG_CLIENT_PASS | FLAG_CLIENT_NICK | FLAG_CLIENT_USER;


/* Access client sur le serveur lui meme */
const AccessType CLIENT_ACCESS_NONE			= 0x0;
const AccessType CLIENT_ACCESS_AWAY 		= 0x1;
const AccessType CLIENT_ACCESS_INVISIBLE	= 0x2;		// +i	| invisible par WHO
const AccessType CLIENT_ACCESS_HIDDEN_HOST	= 0x4;		// +x	| masquage ip: xxx.xxx.xxx.xx => random.username.qwu.org 
const AccessType CLIENT_ACCESS_DEAF 		= 0x8;		// +d	| bloque récéptions message de channels
const AccessType CLIENT_ACCESS_REGISTERED	= 0x10;		// +R	| rejette les message privé
const AccessType CLIENT_ACCESS_WHITELIST	= 0x20;		// +g	| rejette les message privé des personnes à qui tu n'as pas envoyé de message 
const AccessType CLIENT_ACCESS_BOT			= 0x40;		// +B	| indique que l'utilisateur est un bot
const AccessType CLIENT_ACCESS_OPERATOR		= 0x80;		// +oO	| serveur operator
const AccessType CLIENT_ACCESS_ADMIN		= 0x100;	// +aA	| server admin
const AccessType CLIENT_ECHO_MESSAGE		= 0x200;	// si les message doivent se renvoyer a lui meme
const AccessType CLIENT_ACCESS_FULL			= CLIENT_ACCESS_INVISIBLE | CLIENT_ACCESS_HIDDEN_HOST | CLIENT_ACCESS_DEAF | CLIENT_ACCESS_REGISTERED | CLIENT_ACCESS_WHITELIST | CLIENT_ACCESS_BOT | CLIENT_ACCESS_OPERATOR | CLIENT_ACCESS_ADMIN | CLIENT_ACCESS_AWAY;

class Channel;

class Client {
	private:
		Client();
	protected:
		int				_fd;
		std::string		_nick;
		std::string		_userName;
		std::string		_hostName;
		std::string		_serverName;
		std::string		_realName;
		std::string		_bufferOut;
		std::string		_bufferQuit;
		int				_port;
		int				_avertissements;
		AccessType		_userStatus; // if away
		Trie<std::pair<Channel *, AccessType> >	_channel;
	public:
		Client(int socket, std::string host, int port);
		~Client();
		void									setNick(std::string nick);
		const std::string						&getNick() const;
		void									setUserName(std::string user);
		const std::string						&getUserName() const;
		void									setHostName(std::string host);
		const std::string						&getHostName() const;
		void									setServerName(std::string serverName);
		const std::string						&getServerName() const;
		void									setRealName(std::string realName);
		const std::string						&getRealName() const;
		void									setBufferOut(std::string bufferOut);
		void									addBufferOut(std::string bufferOut);
		std::string								&getBufferOut();
		void									setBufferQuit(std::string bufferQuit);
		std::string								&getBufferQuit();
		Trie<std::pair<Channel *, AccessType> >	&getChannel(void);
		void									setFd(int fd);
		int										getFd() const;
		void									setWarning(int warn_lvl);
		int										getWarning() const;
		void									addChannelAccess(const std::string &toCheck, AccessType flag);
		void									delChannelAccess(const std::string &toCheck, AccessType flag) const;
		bool									checkChannelAccess(const std::string &toCheck, AccessType mode) const;
		AccessType								getChannelAccess(const std::string &toCheck) const;
		void									addStatus(AccessType status);
		void									delStatus(AccessType status);
		bool									checkStatus(AccessType status) const;
		AccessType								getStatus() const;
		std::string								buffer;
		uint8_t									quitRequest;
		uint8_t									flagsLogin;
};

#endif
