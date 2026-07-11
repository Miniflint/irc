#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Trie.hpp"
# include <stdint.h>
# include "Channel.hpp"

# define ACCESS_ADM 0x4
# define ACCESS_OPR 0x2
# define ACCESS_USR 0x1

typedef uint8_t AccessType;

class Client {
	protected:
		size_t			_fd;
		std::string		_nick;
		std::string		_user;
		Trie<std::pair<Channel *, AccessType> >	_channel;
		int				_avertissements;
	public:
		Client();
		Client(size_t socket);
		Client(size_t socket, std::string nick);
		void				set_nick(std::string nick);
		const std::string	&get_nick() const;
		void				set_user(std::string user);
		const std::string	&get_user() const;
		void				set_warning(int warn_lvl);
		int					get_warning() const;
		~Client();
		std::string	buffer;
};

#endif