#ifndef SERVER_HPP
# define SERVER_HPP

# include "main.hpp"
# include "Trie.hpp"
# include "Server.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include <iostream>
# include <sstream>
# define SOCK_DOMAIN AF_LOCAL

# define  MAX_SOCKET_FD 2048U
# define  MAX_EVENTS 10U

class Server {
	typedef bool (Server::*cmdFn)(Client &c, std::istringstream &rest);
	private:
		size_t					_pid;
		size_t					_port;
		int						_sockServerFD;
		int						_epfd;
		struct epoll_event		_events[MAX_EVENTS];
		std::string				_password;
		std::string				_ip;
		Trie<Server::cmdFn>		_commands;
		Trie<Client>			_userNickname;
		std::vector<Client *>	_clients;
		Trie<Channel>			_channels;
		bool					_socketInit();
		bool					_epollInit();
		bool					_init();
		bool					_epollLoop();
		bool					_clientAdd();
		bool					_sockServerInit();

		bool					_validateAccess(Client *c, std::string &command);
		bool    				_validateCommand(cmdFn &func, std::string &command);
		Server() {};
		Server(const Server &src) {(void)src;};
	public:
		Server(size_t port, std::string password);
		~Server();
		std::pair<size_t, std::string>	getVals();
		bool 							new_connection(size_t fd);
		bool							run();
		void							doCommand(size_t fd);
		Client							&getClient(size_t fd);
		// c'est horrible
		bool handle_admin(Client &c, std::istringstream &rest);
		bool handle_away(Client &c, std::istringstream &rest);
		bool handle_cnotice(Client &c, std::istringstream &rest);
		bool handle_cprivmsg(Client &c, std::istringstream &rest);
		bool handle_connect(Client &c, std::istringstream &rest);
		bool handle_die(Client &c, std::istringstream &rest);
		bool handle_error(Client &c, std::istringstream &rest);
		bool handle_help(Client &c, std::istringstream &rest);
		bool handle_info(Client &c, std::istringstream &rest);
		bool handle_invite(Client &c, std::istringstream &rest);
		bool handle_ison(Client &c, std::istringstream &rest);
		bool handle_join(Client &c, std::istringstream &rest);
		bool handle_kick(Client &c, std::istringstream &rest);
		bool handle_kill(Client &c, std::istringstream &rest);
		bool handle_knock(Client &c, std::istringstream &rest);
		bool handle_links(Client &c, std::istringstream &rest);
		bool handle_list(Client &c, std::istringstream &rest);
		bool handle_lusers(Client &c, std::istringstream &rest);
		bool handle_mode(Client &c, std::istringstream &rest);
		bool handle_motd(Client &c, std::istringstream &rest);
		bool handle_names(Client &c, std::istringstream &rest);
		bool handle_nick(Client &c, std::istringstream &rest);
		bool handle_notice(Client &c, std::istringstream &rest);
		bool handle_oper(Client &c, std::istringstream &rest);
		bool handle_part(Client &c, std::istringstream &rest);
		bool handle_pass(Client &c, std::istringstream &rest);
		bool handle_ping(Client &c, std::istringstream &rest);
		bool handle_pong(Client &c, std::istringstream &rest);
		bool handle_privmsg(Client &c, std::istringstream &rest);
		bool handle_quit(Client &c, std::istringstream &rest);
		bool handle_quote(Client &c, std::istringstream &rest);
		bool handle_rehash(Client &c, std::istringstream &rest);
		bool handle_rules(Client &c, std::istringstream &rest);
		bool handle_server(Client &c, std::istringstream &rest);
		bool handle_squery(Client &c, std::istringstream &rest);
		bool handle_squit(Client &c, std::istringstream &rest);
		bool handle_setname(Client &c, std::istringstream &rest);
		bool handle_silence(Client &c, std::istringstream &rest);
		bool handle_stats(Client &c, std::istringstream &rest);
		bool handle_summon(Client &c, std::istringstream &rest);
		bool handle_time(Client &c, std::istringstream &rest);
		bool handle_topic(Client &c, std::istringstream &rest);
		bool handle_trace(Client &c, std::istringstream &rest);
		bool handle_user(Client &c, std::istringstream &rest);
		bool handle_userhost(Client &c, std::istringstream &rest);
		bool handle_userip(Client &c, std::istringstream &rest);
		bool handle_users(Client &c, std::istringstream &rest);
		bool handle_version(Client &c, std::istringstream &rest);
		bool handle_wallops(Client &c, std::istringstream &rest);
		bool handle_watch(Client &c, std::istringstream &rest);
		bool handle_who(Client &c, std::istringstream &rest);
		bool handle_whois(Client &c, std::istringstream &rest);
		bool handle_whowas(Client &c, std::istringstream &rest);
		bool handle_message(Client &c, std::istringstream &rest);
};

#endif
