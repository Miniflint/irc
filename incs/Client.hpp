#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Trie.hpp"
# include <stdint.h>
# include "Channel.hpp"
# include <sys/socket.h>

# define ACCESS_ADM 0x4
# define ACCESS_OPR 0x2
# define ACCESS_USR 0x1

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
		struct sockaddr	_addr;
		socklen_t		_addrLen;
		int				_avertissements;
		Trie<std::pair<Channel *, AccessType> >	_channel;
	public:
		Client(int socket, struct sockaddr addr, socklen_t addrLen);
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
		std::string								getBufferOut() const;
		Trie<std::pair<Channel *, AccessType> >	getChannel(void) const;
		void									setFd(size_t fd);
		size_t									getFd() const;
		void									setWarning(int warn_lvl);
		int										getWarning() const;
		void									addAccess(const std::string &toCheck, AccessType flag);
		void									delAccess(const std::string &toCheck, AccessType flag) const;
		bool									checkFlag(const std::string &toCheck, AccessType mode) const;
		struct sockaddr							&getAddr();
		socklen_t								&getAddrLen();
		std::string	buffer;
};

#endif