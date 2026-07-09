#ifndef SERVER_HPP
# define SERVER_HPP

# include "main.hpp"
# include <map>
# include <sys/socket.h>
# define FD_SET_MAX 2048
# define MAX_EVENTS 10
# define SOCK_DOMAIN AF_LOCAL

class Server {
	typedef bool (Server::*cmdFn)(std::string &rest);
	private:
		size_t				_pid;
		size_t				_port;
		int					_sockServerFD;
		int					_epfd;
		struct epoll_event	_events[MAX_EVENTS];
		std::string			_password;
		std::string			_ip;
		Trie<Server::cmdFn>	_commands;
		Trie<Client>		_clients;
		Trie<Client>		_clientsAnon;
		Trie<Channel>		_channels;
		bool				_socketInit();
		bool				_epollInit();
		bool				_init();
		bool				_epollLoop();
		bool				_clientAdd();
		Server() {};
		Server(const Server &src) {};
	public:
		Server(size_t port, std::string password);
		~Server();
		std::pair<size_t, std::string>	getVals();
		bool 							new_connection();
		bool							run();
		Server::cmdFn					do_command(std::size_t fd, std::string &lookup, std::string &rest);
		// c'est horrible
		bool handle_admin(std::string &rest);
		bool handle_away(std::string &rest);
		bool handle_cnotice(std::string &rest);
		bool handle_cprivmsg(std::string &rest);
		bool handle_connect(std::string &rest);
		bool handle_die(std::string &rest);
		bool handle_error(std::string &rest);
		bool handle_help(std::string &rest);
		bool handle_info(std::string &rest);
		bool handle_invite(std::string &rest);
		bool handle_ison(std::string &rest);
		bool handle_join(std::string &rest);
		bool handle_kick(std::string &rest);
		bool handle_kill(std::string &rest);
		bool handle_knock(std::string &rest);
		bool handle_links(std::string &rest);
		bool handle_list(std::string &rest);
		bool handle_lusers(std::string &rest);
		bool handle_mode(std::string &rest);
		bool handle_motd(std::string &rest);
		bool handle_names(std::string &rest);
		bool handle_nick(std::string &rest);
		bool handle_notice(std::string &rest);
		bool handle_oper(std::string &rest);
		bool handle_part(std::string &rest);
		bool handle_pass(std::string &rest);
		bool handle_ping(std::string &rest);
		bool handle_pong(std::string &rest);
		bool handle_privmsg(std::string &rest);
		bool handle_quit(std::string &rest);
		bool handle_quote(std::string &rest);
		bool handle_rehash(std::string &rest);
		bool handle_rules(std::string &rest);
		bool handle_server(std::string &rest);
		bool handle_squery(std::string &rest);
		bool handle_squit(std::string &rest);
		bool handle_setname(std::string &rest);
		bool handle_silence(std::string &rest);
		bool handle_stats(std::string &rest);
		bool handle_summon(std::string &rest);
		bool handle_time(std::string &rest);
		bool handle_topic(std::string &rest);
		bool handle_trace(std::string &rest);
		bool handle_user(std::string &rest);
		bool handle_userhost(std::string &rest);
		bool handle_userip(std::string &rest);
		bool handle_users(std::string &rest);
		bool handle_version(std::string &rest);
		bool handle_wallops(std::string &rest);
		bool handle_watch(std::string &rest);
		bool handle_who(std::string &rest);
		bool handle_whois(std::string &rest);
		bool handle_whowas(std::string &rest);
		bool handle_message(std::string &rest);
};

#endif
