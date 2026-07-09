#include "Server.hpp"


Server::Server(size_t port, std::string password) : _port(port), _password(password), _ip(std::string("0.0.0.0"))
{
    const std::string t[] = {
    "ADMIN", "AWAY", "CNOTICE", "CPRIVMSG", "CONNECT", "DIE", "ERROR",
    "HELP", "INFO", "INVITE", "ISON", "JOIN", "KICK", "KILL", "KNOCK",
    "LINKS","LIST","LUSERS","MODE","MOTD","NAMES","NICK","NOTICE","OPER",
    "PART","PASS","PING","PONG","PRIVMSG","QUIT","QUOTE","REHASH","RULES",
    "SERVER","SQUERY","SQUIT","SETNAME","SILENCE","STATS","SUMMON",
    "TIME","TOPIC","TRACE","USER","USERHOST","USERIP","USERS","VERSION",
    "WALLOPS","WATCH","WHO","WHOIS","WHOWAS", ":"
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
        &Server::handle_rules, &Server::handle_server, &Server::handle_squery, &Server::handle_squit,
        &Server::handle_setname, &Server::handle_silence, &Server::handle_stats, &Server::handle_summon,
        &Server::handle_time, &Server::handle_topic, &Server::handle_trace, &Server::handle_user,
        &Server::handle_userhost, &Server::handle_userip, &Server::handle_users, &Server::handle_version,
        &Server::handle_wallops, &Server::handle_watch, &Server::handle_who, &Server::handle_whois,
        &Server::handle_whowas, &Server::handle_message
    };
    for (unsigned int i = 0; i <= END; i++)
        this->_commands.add(t[i], func_list[i]);
    this->_commands.create_graph();
}

Server::~Server()
{
}

bool            Server::_epollInit()
{
    struct epoll_event      server_event;

    this->_epfd = epoll_create1(0);
    if (this->_epfd == -1)
        return (false);
    server_event.events = EPOLLIN;
    server_event.data.fd = this->_sockServerFD;
    epoll_ctl(this->_epfd, EPOLL_CTL_ADD, this->_sockServerFD, &server_event);
    return (true);
}

bool            Server::_epollLoop()
{
    int     nfds;
    while (1)
    {
        nfds = epoll_wait(this->_epfd, this->events, MAX_EVENTS, -1);
        if (nfds == -1)
            return (false);
        for (int i = 0; i < nfds; ++i)
        {
            if (this->events[i].data.fd == this->_sockServerFD)
            {
                this->clientAdd()
            }
            else if (events[i].events & EPOLLIN)
            {

            }
            else if (events[i].events & EPOLLOUT)
            {

            }
            else if (events[i].events & EPOLLHUP || events[i].events & EPOLLERR)
            {

            }
        }
    }
}

bool        Server::run()
{
    
}
bool Server::_clientAdd()
{
    std::size_t t;

    t = 5;
    Client c(t);
    this->_clients.push_front(c);
    return (0);
};

Server::cmdFn	Server::do_command(std::size_t fd, std::string &lookup, std::string &rest)
{
    cmdFn t = this->_commands[lookup];

    (void)fd;
    std::string test(rest);
    (this->*t)(test);
    return (t);
}

