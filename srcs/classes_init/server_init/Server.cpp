#include "Server.hpp"
#include <algorithm>

Server::Server(size_t port, std::string password) : _port(port), _password(password), _ip(std::string("0.0.0.0"))
{
    this->_clients.assign(MAX_SOCKET_FD, NULL);
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
    const std::vector<Client *>::const_iterator end = this->_clients.end();
    for (std::vector<Client *>::iterator it = this->_clients.begin(); it != end; it++)
        if (*it) { delete *it; *it = NULL; }
    this->_clients.clear();
}

bool            Server::_epollInit()
{
    struct epoll_event      server_event;
    
    this->_epfd = epoll_create1(0);
    if (this->_epfd == -1)
        return (false);
    server_event.events = EPOLLIN;
    server_event.data.fd = this->_sockServerFD;
    (void)server_event;
    return (true);
}

bool    Server::_validateAccess(Client *c, std::string &command)
{
    if (command == "NICK" || command == "USER")
        return (true);
    try {
        const std::string nick = c->getNick();
        if (c->getUserName().empty() || nick.empty())
            throw std::exception();
        (void)this->_userNickname[nick];
    } catch (std::exception &e) {
        std::cerr << "[ERROR]: User not authorized" << std::endl;
        c->buffer = "";
        return (false);
    }
    return (true);
}

bool    Server::_validateCommand(cmdFn &func, std::string &command)
{
    try {
        func = this->_commands[command];
    } catch (std::exception &e) {
        std::cerr << "[ERROR]: " << command << " does not exist" << std::endl;
        return (false);
    };
    return (true);
}

void	Server::doCommand(size_t fd) //Est-ce qu'il y a une commande fini
{
    Client *c = this->_clients[fd];
    if (!c || c->buffer.size() < 2 || c->buffer.compare(c->buffer.length() - 2, std::string::npos, "\r\n"))
        return ;
    std::istringstream  iss(c->buffer);
    std::string         cmd;
    cmdFn               func;
    iss >> cmd;
    if (!this->_validateCommand(func, cmd) || !this->_validateAccess(c, cmd))
    {
        const int warnings = c->get_warning() + 1;
        c->set_warning(warnings);
        // kick user
        if (warnings > 2)
            {}
        std::cout << "You get a warning (" << warnings << ")" << std::endl;
        return ;
    }
    (this->*func)(*c, iss);
}

bool Server::new_connection(size_t fd)
{
    return ((this->_clients[fd] = new Client(fd, "")) != NULL);
}

Client	&Server::getClient(size_t fd)
{
    return (*(this->_clients[fd]));
}
