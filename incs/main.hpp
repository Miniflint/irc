#ifndef MAIN_HPP
# define MAIN_HPP

# include <string>
# include <iostream>
# include <list>

# define LOCALHOST "127.0.0.1"

enum E_commands {
	ADMIN, // Instructs the server to return information about the administrators of the server specified by <target>,
	AWAY, // Provides the server with a message to automatically send in reply to a PRIVMSG directed at the user
	CNOTICE,
	CPRIVMSG,
	CONNECT,
	DIE,
	ENCAP,
	ERROR,
	HELP,
	INFO,
	INVITE,
	ISON,
	JOIN,
	KICK,
	KILL,
	KNOCK,
	LINKS,
	LIST,
	LUSERS,
	MODE,
	MOTD,
	NAMES,
	NICK,
	NOTICE,
	OPER,
	PART,
	PASS,
	PING,
	PONG,
	PRIVMSG,
	QUIT,
	QUOTE,
	REHASH,
	RULES,
	SERVER,
	SERVICE,
	SERVLIST,
	SQUERY,
	SQUIT,
	SETNAME,
	SILENCE,
	STATS,
	SUMMON,
	TIME,
	TOPIC,
	TRACE,
	USER,
	USERHOST,
	USERIP,
	USERS,
	VERSION,
	WALLOPS,
	WATCH,
	WHO,
	WHOIS,
	WHOWAS,
	END
};

class Client;
class Server;
class Channel;

# include "server.hpp"
# include "client.hpp"
# include "channel.hpp"

#endif