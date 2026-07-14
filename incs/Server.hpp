#ifndef SERVER_HPP
# define SERVER_HPP

# include "main.hpp"
# include "Trie.hpp"
# include "Server.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include <iostream>
# include <sstream>
# include <queue>
# define SOCK_DOMAIN AF_LOCAL
# define SERV_HOST_NAME "ft_irc.42.com"

# define  MAX_SOCKET_FD 2048U

typedef struct S_ChannelSpecifiers {
	std::string	channelType;
	std::string	channelMode;
	uint16_t	channelLen;
	std::string	channelAuthPrefix;
}	t_ChannelSpecifiers;

typedef struct S_ClientSpecifiers {
	uint16_t	nickLenMax;
}	t_ClientSpecifiers;

typedef struct S_Motd {
	std::string					motd;
	std::vector<std::string>	announcements;
}	t_Motd;

class Server {
	typedef bool (Server::*cmdFn)(Client &c, std::istringstream &rest);
	private:
		uint16_t				_port;
		int						_sockServerFD;
		std::string				_password;
		std::string				_host;
		Trie<Server::cmdFn>		_commands;
		Trie<int>				_clientTrie;
		std::vector<Client *>	_clients;
		Trie<Channel *>			_channelTrie;
		std::list<Channel>		_channel;
		t_ChannelSpecifiers		_channelSpecifiers;
		t_ClientSpecifiers		_clientSpecifiers;
		t_Motd					_motd;
		// bool					_init();
		// bool					_clientAdd();

		bool					_validateAccess(Client &c, std::string &command);
		bool    				_validateCommand(Client &c, cmdFn &func, std::string &command);
		const std::string		&_getPassword();
		std::string 			_rplPrefix(std::string code, std::string nick) const;
		void					_sendAllWelcome(Client &c);
		Server() {};
		Server(const Server &src) {(void)src;};
	public:
		Server(uint16_t port, std::string password);
		~Server();
		// std::pair<size_t, std::string>	getVals();
		int 							newConnection();
		void							delClient(int fd);
		bool							run();
		bool							doCommand(size_t fd);
		Client							&getClient(size_t fd);
		// void							setClient(size_t fd);
		std::string						getIp(void) const;
		void							setIp(std::string ip);
		bool							sendToClient(Client &source, std::string message);
		void							deconnectClient(int fd, std::string error, std::string message);
		std::queue<int>					poolOut;
		std::vector<int>				poolQuit;
		// std::vector<int>				poolInt;
		// c'est horrible
		bool handle_admin(Client &c, std::istringstream &rest);
		bool handle_away(Client &c, std::istringstream &rest);
		bool handle_cap(Client &c, std::istringstream &iss);
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
		bool handleNick(Client &c, std::istringstream &rest);
		bool handle_notice(Client &c, std::istringstream &rest);
		bool handle_oper(Client &c, std::istringstream &rest);
		bool handle_part(Client &c, std::istringstream &rest);
		bool handlePass(Client &c, std::istringstream &rest);
		bool handlePing(Client &c, std::istringstream &rest);
		bool handle_pong(Client &c, std::istringstream &rest);
		bool handlePrivMsg(Client &c, std::istringstream &rest);
		bool handleQuit(Client &c, std::istringstream &rest);
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
		bool handleUser(Client &c, std::istringstream &rest);
		bool handle_userhost(Client &c, std::istringstream &rest);
		bool handle_userip(Client &c, std::istringstream &rest);
		bool handle_users(Client &c, std::istringstream &rest);
		bool handle_version(Client &c, std::istringstream &rest);
		bool handle_wallops(Client &c, std::istringstream &rest);
		bool handle_watch(Client &c, std::istringstream &rest);
		bool handle_who(Client &c, std::istringstream &rest);
		bool handle_whois(Client &c, std::istringstream &rest);
		bool handle_whowas(Client &c, std::istringstream &rest);
		bool handleDcc(Client &c, std::istringstream &rest);
		bool handle_message(Client &c, std::istringstream &rest);
		void handleRplWelcome(Client &c);
		void handleRplYourhost(Client &c);
		void handleRplCreated(Client &c);
		void handleRplMyinfo(Client &c);
		void handleRplISupport(Client &c);
		void handleRplTracelink(Client &c);
		void handleRplTraceconnecting(Client &c);
		void handleRplTracehandshake(Client &c);
		void handleRplTraceunknown(Client &c);
		void handleRplTraceoperator(Client &c);
		void handleRplTraceuser(Client &c);
		void handleRplTraceserver(Client &c);
		void handleRplTraceservice(Client &c);
		void handleRplTracenewtype(Client &c);
		void handleRplTraceclass(Client &c);
		void handleRplTracereconnect(Client &c);
		void handleRplStatslinkinfo(Client &c);
		void handleRplStatscommands(Client &c);
		void handleRplStatscline(Client &c);
		void handleRplStatsnline(Client &c);
		void handleRplStatsiline(Client &c);
		void handleRplStatskline(Client &c);
		void handleRplStatsqline(Client &c);
		void handleRplStatsyline(Client &c);
		void handleRplEndofstats(Client &c);
		void handleRplUmodeis(Client &c);
		void handleRplServiceinfo(Client &c);
		void handleRplEndofservices(Client &c);
		void handleRplService(Client &c);
		void handleRplServlist(Client &c);
		void handleRplServlistend(Client &c);
		void handleRplStatsvline(Client &c);
		void handleRplStatslline(Client &c);
		void handleRplStatsuptime(Client &c);
		void handleRplStatsoline(Client &c);
		void handleRplStatshline(Client &c);
		void handleRplStatsping(Client &c);
		void handleRplStatsbline(Client &c);
		void handleRplStatsdline(Client &c);
		void handleRplLuserclient(Client &c);
		void handleRplLuserop(Client &c);
		void handleRplLuserunknown(Client &c);
		void handleRplLuserchannels(Client &c);
		void handleRplLuserme(Client &c);
		void handleRplAdminme(Client &c);
		void handleRplAdminloc1(Client &c);
		void handleRplAdminloc2(Client &c);
		void handleRplAdminemail(Client &c);
		void handleRplTracelog(Client &c);
		void handleRplTraceend(Client &c);
		void handleRplTryagain(Client &c);
		void handleRplNone(Client &c);
		void handleRplAway(Client &c);
		void handleRplUserhost(Client &c);
		void handleRplIson(Client &c);
		void handleRplUnaway(Client &c);
		void handleRplNowaway(Client &c);
		void handleRplWhoisuser(Client &c);
		void handleRplWhoisserver(Client &c);
		void handleRplWhoisoperator(Client &c);
		void handleRplWhowasuser(Client &c);
		void handleRplEndofwho(Client &c);
		void handleRplWhoischanop(Client &c);
		void handleRplWhoisidle(Client &c);
		void handleRplEndofwhois(Client &c);
		void handleRplWhoischannels(Client &c);
		void handleRplListstart(Client &c);
		void handleRplList(Client &c);
		void handleRplListend(Client &c);
		void handleRplChannelmodeis(Client &c);
		void handleRplUniqopis(Client &c);
		void handleRplNotopic(Client &c);
		void handleRplTopic(Client &c);
		void handleRplInviting(Client &c);
		void handleRplSummoning(Client &c);
		void handleRplInvitelist(Client &c);
		void handleRplEndofinvitelist(Client &c);
		void handleRplExceptlist(Client &c);
		void handleRplEndofexceptlist(Client &c);
		void handleRplVersion(Client &c);
		void handleRplWhoreply(Client &c);
		void handleRplNamreply(Client &c);
		void handleRplKilldone(Client &c);
		void handleRplClosing(Client &c);
		void handleRplCloseend(Client &c);
		void handleRplLinks(Client &c);
		void handleRplEndoflinks(Client &c);
		void handleRplEndofnames(Client &c);
		void handleRplBanlist(Client &c);
		void handleRplEndofbanlist(Client &c);
		void handleRplEndofwhowas(Client &c);
		void handleRplInfo(Client &c);
		void handleRplMotd(Client &c);
		void handleRplInfostart(Client &c);
		void handleRplEndofinfo(Client &c);
		void handleRplMotdstart(Client &c);
		void handleRplEndofmotd(Client &c);
		void handleRplYoureoper(Client &c);
		void handleRplRehashing(Client &c);
		void handleRplYoureservice(Client &c);
		void handleRplMyportis(Client &c);
		void handleRplTime(Client &c);
		void handleRplUsersstart(Client &c);
		void handleRplUsers(Client &c);
		void handleRplEndofusers(Client &c);
		void handleRplNousers(Client &c);
		void handleErrNoSuchNick(Client &c, std::string clientName);
		void handleErrNosuchserver(Client &c);
		void handleErrNosuchchannel(Client &c, std::string channelName);
		void handleErrCannotSendToChan(Client &c, std::string channelName);
		void handleErrToomanychannels(Client &c);
		void handleErrWasnosuchnick(Client &c);
		void handleErrToomanytargets(Client &c);
		void handleErrNosuchservice(Client &c);
		void handleErrNoorigin(Client &c);
		void handleErrNoRecipient(Client &c, std::string cmd);
		void handleErrNotexttosend(Client &c);
		void handleErrNotoplevel(Client &c);
		void handleErrWildtoplevel(Client &c);
		void handleErrBadmask(Client &c);
		void handleErrUnknowncommand(Client &c, std::string &cmd);
		void handleErrNomotd(Client &c);
		void handleErrNoadmininfo(Client &c);
		void handleErrFileerror(Client &c);
		void handleErrNoNicknameGiven(Client &c);
		void handleErrErroneousNickname(Client &c, std::string targetNickName);
		void handleErrNicknameInUse(Client &c, std::string targetNickName);
		void handleErrNickCollision(Client &c, std::string targetNickName);
		void handleErrUnavailresource(Client &c);
		void handleErrUsernotinchannel(Client &c);
		void handleErrNotonchannel(Client &c);
		void handleErrUseronchannel(Client &c);
		void handleErrNologin(Client &c);
		void handleErrSummondisabled(Client &c);
		void handleErrUsersdisabled(Client &c);
		void handleErrNotregistered(Client &c);
		void handleErrNeedMoreParams(Client &c, std::string cmd);
		void handleErrAlreadyRegistered(Client &c);
		void handleErrNopermforhost(Client &c);
		void handleErrPasswdMismatch(Client &c);
		void handleErrYourebannedcreep(Client &c);
		void handleErrYouwillbebanned(Client &c);
		void handleErrKeyset(Client &c);
		void handleErrChannelisfull(Client &c);
		void handleErrUnknownmode(Client &c);
		void handleErrInviteonlychan(Client &c);
		void handleErrBannedfromchan(Client &c);
		void handleErrBadchannelkey(Client &c);
		void handleErrBadchanmask(Client &c);
		void handleErrNochanmodes(Client &c);
		void handleErrBanlistfull(Client &c);
		void handleErrNoprivileges(Client &c);
		void handleErrChanoprivsneeded(Client &c);
		void handleErrCantkillserver(Client &c);
		void handleErrRestricted(Client &c);
		void handleErrUniqoprivsneeded(Client &c);
		void handleErrNooperhost(Client &c);
		void handleErrNoservicehost(Client &c);
		void handleErrUmodeunknownflag(Client &c);
		void handleErrUsersdontmatch(Client &c);
};

#endif
