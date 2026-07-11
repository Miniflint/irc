#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Trie.hpp"
# include <stdint.h>
# include "Channel.hpp"

# define ACCESS_ADM 0x4
# define ACCESS_OPR 0x2
# define ACCESS_USR 0x1

typedef uint8_t AccessType;

class Channel;

class Client {
	protected:
		size_t			_fd;
		std::string		_nick;
		std::string		_userName;
		std::string		_hostName;
		std::string		_serverName;
		std::string		_realName;
		int				_avertissements;
		Trie<std::pair<Channel *, AccessType> >	_channel;
	public:
		Client();
		Client(size_t socket);
		Client(size_t socket, std::string nick);
		Client(size_t socket, std::string nick, std::string host);
		void				setNick(std::string nick);
		const std::string	&getNick() const;
		void				setUserName(std::string user);
		const std::string	&getUserName() const;
		void				setHostName(std::string host);
		const std::string	&getHostName() const;
		void				setServerName(std::string serverName);
		const std::string	&getServerName() const;
		void				setRealName(std::string realName);
		const std::string	&getRealName() const;
		void				setWarning(int warn_lvl);
		int					getWarning() const;
		~Client();
		std::string	buffer;
};

#endif