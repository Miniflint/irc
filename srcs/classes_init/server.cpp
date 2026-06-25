#include "main.hpp"

Server::Server(unsigned int port, std::string password) : _port(port), _password(password), _ip(std::string("0.0.0.0"))
{
    const std::string t[] = {
    "ADMIN", "ADMIRN", "ADMRIS", "AWAY", "CNOTICE", "CPRIVMSG",
    "CONNECT", "DIE", "ENCAP", "ERROR", "HELP", "INFO", "INVITE",
    "ISON", "JOIN", "KICK", "KILL", "KNOCK", "LINKS", "LIST", "LUSERS",
    "MODE", "MOTD", "NAMES", "NICK", "NOTICE", "OPER", "PART",
    "PASS", "PING", "PONG", "PRIVMSG", "QUIT", "QUOTE", "REHASH", "RULES",
    "SERVER", "SERVICE", "SERVLIST", "SQUERY", "SQUIT", "SETNAME",
    "SILENCE", "STATS", "SUMMON", "TIME", "TOPIC", "TRACE", "USER", "USERHOST",
    "USERIP", "USERS", "VERSION", "WALLOPS", "WATCH", "WHO", "WHOIS", "WHOWAS",
    }

    for (std::list<std::string>::iterator i = t.begin(); i != t.end(); i++)
        this->_commands.add(*i, nullptr);
}
