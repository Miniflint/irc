#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Trie.hpp"
# include <stdint.h>
# include "Channel.hpp"
# include <sys/socket.h>

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
const uint8_t CHECK_CLIENT_LOG = 0x7;

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
		uint8_t			_flagsUser; // if away
		Trie<std::pair<Channel *, AccessType> >	_channel;
	public:
		Client(int socket, std::string host, int port);
		~Client();
		void											setNick(std::string nick);
		const std::string								&getNick() const;
		void											setUserName(std::string user);
		const std::string								&getUserName() const;
		void											setHostName(std::string host);
		const std::string								&getHostName() const;
		void											setServerName(std::string serverName);
		const std::string								&getServerName() const;
		void											setRealName(std::string realName);
		const std::string								&getRealName() const;
		void											setBufferOut(std::string bufferOut);
		void											addBufferOut(std::string bufferOut);
		std::string										&getBufferOut();
		void											setBufferQuit(std::string bufferQuit);
		std::string										&getBufferQuit();
		Trie<std::pair<Channel *, AccessType> >			&getChannel(void);
		void											setFd(size_t fd);
		size_t											getFd() const;
		void											setWarning(int warn_lvl);
		int												getWarning() const;
		void											addAccess(const std::string &toCheck, AccessType flag);
		void											delAccess(const std::string &toCheck, AccessType flag) const;
		bool											checkFlag(const std::string &toCheck, AccessType mode) const;
		std::string										buffer;
		uint8_t											quitRequest;
		uint8_t											flagsLogin;
};

#endif
