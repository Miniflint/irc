#ifndef MAIN_HPP
# define MAIN_HPP

# include <string>
# include <iostream>
# include <list>

# define LOCALHOST "127.0.0.1"

# include "trie.hpp"

class Client;
class Server;
class Channel;

# include "server.hpp"
# include "client.hpp"
# include "channel.hpp"

enum E_commands {
	ADMIN, // ADMIN [<target>]
	AWAY, // AWAY [<message>]
	CNOTICE, // CNOTICE <nickname> <channel> :<message>
	CPRIVMSG, // CPRIVMSG <nickname> <channel> :<message>
	CONNECT, // CONNECT <target server> [<port> [<remote server>]] (RFC 1459)
	DIE, // DIE
	ERROR, // ERROR <error message>
	HELP, // HELP
	INFO, // INFO [<target>]
	INVITE, // INVITE <nickname> <channel>
	ISON, // ISON <nicknames>
	JOIN, // JOIN <channels> [<keys>]
	KICK, // KICK <channel> <client> :[<message>]
	KILL, // KILL <client> <comment>
	KNOCK, // KNOCK <channel> [<message>]
	LINKS, // LINKS [<remote server> [<server mask>]]
	LIST, // LIST [<channels> [<server>]]
	LUSERS, // LUSERS [<mask> [<server>]]
	MODE, // MODE <nickname> <flags> (user)
	MOTD, // MOTD [<server>]
	NAMES, // NAMES [<channels>] (RFC 1459)
	NICK, // NICK <nickname> [<hopcount>] (RFC 1459)
	NOTICE, // NOTICE <msgtarget> <message>
	OPER, // OPER <username> <password>
	PART, // PART <channels> [<message>]
	PASS, // PASS <password>
	PING, // PING <server1> [<server2>]
	PONG, // PONG <server1> [<server2>]
	PRIVMSG, // PRIVMSG <msgtarget> :<message>
	QUIT, // QUIT [<message>]
	QUOTE, // QUOTE
	REHASH, // REHASH
	RULES, // RULES
	SERVER, // SERVER <servername> <hopcount> <info>
	SQUERY, // SQUERY <servicename> <text>
	SQUIT, // SQUIT <server> <comment>
	SETNAME, // SETNAME <new real name>
	SILENCE, // SILENCE [+/-<hostmask>]
	STATS, // STATS <query> [<server>]
	SUMMON, // SUMMON <user> [<server>] (RFC 1459)
	TIME, // TIME [<server>]
	TOPIC, // TOPIC <channel> [<topic>]
	TRACE, // TRACE [<target>]
	USER, // USER <username> <hostname> <servername> <realname> (RFC 1459)
	USERHOST, // USERHOST <nickname> [<nickname> <nickname> ...]
	USERIP, // USERIP <nickname>
	USERS, // USERS [<server>]
	VERSION, // VERSION [<server>]
	WALLOPS, // WALLOPS <message>
	WATCH, // WATCH [+/-<nicknames>]
	WHO, // WHO [<name> ["o"]]
	WHOIS, // WHOIS [<server>] <nicknames>
	WHOWAS, // WHOWAS <nickname> [<count> [<server>]]
	END
};

#endif