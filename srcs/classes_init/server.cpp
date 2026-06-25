#include "server.hpp"

Server::Server(unsigned int port, std::string password) : _port(port), _password(password), _ip(std::string("0.0.0.0"))
{
    const std::string t[] = {
    "ADMIN", "AWAY", "CNOTICE", "CPRIVMSG", "CONNECT", "DIE", "ERROR",
    "HELP", "INFO", "INVITE", "ISON", "JOIN", "KICK", "KILL", "KNOCK",
    "LINKS","LIST","LUSERS","MODE","MOTD","NAMES","NICK","NOTICE","OPER",
    "PART","PASS","PING","PONG","PRIVMSG","QUIT","QUOTE","REHASH","RULES",
    "SERVER","SQUERY","SQUIT","SETNAME","SILENCE","STATS","SUMMON",
    "TIME","TOPIC","TRACE","USER","USERHOST","USERIP","USERS","VERSION",
    "WALLOPS","WATCH","WHO","WHOIS","WHOWAS"
    };

    const Server::cmdFn func_list[] = {
        &Server::handle_admin, &Server::handle_away, &Server::handle_cnotice, &Server::handle_cprivmsg,
        &Server::handle_connect, &Server::handle_die, &Server::handle_error, &Server::handle_help,
        &Server::handle_info, &Server::handle_invite, &Server::handle_ison, &Server::handle_join,
        &Server::handle_kick, &Server::handle_kill, &Server::handle_knock, &Server::handle_links,
        &Server::handle_list, &Server::handle_lusers, &Server::handle_mode, &Server::handle_motd,
        &Server::handle_names, &Server::handle_nick, &Server::handle_notice, &Server::handle_oper,
        &Server::handle_part, &Server::handle_pass, &Server::handle_ping, &Server::handle_pong,
        &Server::handle_privmsg, &Server::handle_quit, &Server::handle_quote, &Server::handle_rehash,
        &Server::handle_rules, &Server::handle_server, &Server::handle_squery,
        &Server::handle_squit, &Server::handle_setname, &Server::handle_silence, &Server::handle_stats,
        &Server::handle_summon, &Server::handle_time, &Server::handle_topic, &Server::handle_trace,
        &Server::handle_user, &Server::handle_userhost, &Server::handle_userip, &Server::handle_users,
        &Server::handle_version, &Server::handle_wallops, &Server::handle_watch, &Server::handle_who,
        &Server::handle_whois, &Server::handle_whowas
    };
    for (unsigned int i = 0; i < END; i++)
        this->_commands.add(t[i], func_list[i]);
    this->_commands.create_graph();
}

Server::~Server()
{
}

Server::cmdFn	Server::do_command(std::string &lookup, std::string &rest)
{
    cmdFn t = this->_commands[lookup];

    std::string test(rest);
    (this->*t)(test);
    return (t);
}