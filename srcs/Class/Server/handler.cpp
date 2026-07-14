#include "Server.hpp"
#include <cstring>
template <typename T>
static	bool _checkInTrieExist(Trie<T> &trie, const std::string &toCheck)
{
	try {
		(void)trie[toCheck];
	} catch (std::exception &e) {
		return (true);
	}
	return (false);
}

static bool _constantTimeCheck(const std::string &pass, const std::string &toCheck)
{
	unsigned char diff = 0;
	for (unsigned int i = 0; i < pass.size(); i++) {
		diff |= static_cast<unsigned char>(pass[i] ^ toCheck[i]);
	}
	return (diff == 0);
}

static std::string	_formatBaseRelayMessage(Client &c, std::string functionName)
{
	std::string rtn;
	const size_t totalSize = rtn.size() + 5 + c.getNick().size() +
		c.getUserName().size() + c.getHostName().size() + functionName.size();

	rtn.reserve(totalSize);
	rtn.append(1, ':').append(c.getNick()).append(1, '!').append(c.getUserName())
		.append(1, '@').append(c.getHostName()).append(1, ' ').append(functionName)
		.append(1, ' ');
	return (rtn);
}
/* 
static std::string	_formatBaseServerMessage(Server &serv, Client &c, std::string code)
{
	std::string rtn;

	const size_t totalSize = 5 + serv.getIp().size() + code.size() + c.getNick().size();
	rtn.reserve(totalSize);
	rtn.append(1, ' ').append(serv.getIp()).append(1, ' ').append(code)
		.append(1, ' ').append(c.getNick()).append(1, ' ').append(1, ':');
	return (rtn);
}
*/
bool	Server::handle_admin(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "admin: " << token << std::endl;
	return (true);
}
bool	Server::handle_away(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "away: " << token << std::endl;
	return (true);
}
bool	Server::handle_cnotice(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "cnotice: " << token << std::endl;
	return (true);
}
bool	Server::handle_cprivmsg(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "cprivmsg: " << token << std::endl;
	return (true);
}
bool	Server::handle_connect(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "connect: " << token << std::endl;
	return (true);
}
bool	Server::handle_die(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "die: " << token << std::endl;
	return (true);
}
bool	Server::handle_error(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "error: " << token << std::endl;
	return (true);
}
bool	Server::handle_help(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "help: " << token << std::endl;
	return (true);
}
bool	Server::handle_info(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "info: " << token << std::endl;
	return (true);
}
bool	Server::handle_invite(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "invite: " << token << std::endl;
	return (true);
}
bool	Server::handle_ison(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "ison: " << token << std::endl;
	return (true);
}
bool	Server::handle_join(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "join: " << token << std::endl;
	return (true);
}
bool	Server::handle_kick(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "kick: " << token << std::endl;
	return (true);
}
bool	Server::handle_kill(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "kill: " << token << std::endl;
	return (true);
}
bool	Server::handle_knock(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "knock: " << token << std::endl;
	return (true);
}
bool	Server::handle_links(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "links: " << token << std::endl;
	return (true);
}
bool	Server::handle_list(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "list: " << token << std::endl;
	return (true);
}
bool	Server::handle_lusers(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "lusers: " << token << std::endl;
	return (true);
}
bool	Server::handle_mode(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "mode: " << token << std::endl;
	return (true);
}
bool	Server::handle_motd(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "motd: " << token << std::endl;
	return (true);
}
bool	Server::handle_names(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "names: " << token << std::endl;
	return (true);
}
bool	Server::handleNick(Client &c, std::istringstream &iss) 
{
	if (!(c.flagsLogin & FLAG_CLIENT_PASS))
		return (this->handleErrNotregistered(c), this->poolOut.push(c.getFd()), false);
	std::string token;

	iss >> token >> std::noskipws;
	if (iss.fail())
		return (this->handleErrNoNicknameGiven(c), this->poolOut.push(c.getFd()), false);
	if (token.empty() || token.length() > 9)
		return (this->handleErrNoNicknameGiven(c), this->poolOut.push(c.getFd()), false);
	if (token[0] == ':' || this->_channelSpecifiers.channelType.find(token[0]) != std::string::npos)
		return (this->handleErrNickCollision(c, token), this->poolOut.push(c.getFd()), false);
	if (!_checkInTrieExist(this->_clientTrie, token))
		return (this->handleErrNicknameInUse(c, token), this->poolOut.push(c.getFd()), false);
	std::string oldUserName = c.getNick();
	if (c.flagsLogin == CHECK_CLIENT_LOG)
	{
		this->_clientTrie.del(oldUserName);
		// faire message pour changement de nom
	}
	c.setNick(token);
	if (c.flagsLogin & FLAG_CLIENT_USER)
	{
		this->_clientTrie.add(token, c.getFd());
		if (!(c.flagsLogin & FLAG_CLIENT_NICK))
			this->_sendAllWelcome(c);
	}
	c.flagsLogin |= FLAG_CLIENT_NICK;
	return (true);
}
bool	Server::handle_notice(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "notice: " << token << std::endl;
	return (true);
}
bool	Server::handle_oper(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "oper: " << token << std::endl;
	return (true);
}
bool	Server::handle_part(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "part: " << token << std::endl;
	return (true);
}
bool	Server::handlePass(Client &c, std::istringstream &iss) 
{
	if (c.flagsLogin & FLAG_CLIENT_PASS)
		return (this->handleErrAlreadyRegistered(c) ,this->poolOut.push(c.getFd()), false);
	std::string token;
	iss >> token;
	if (iss.fail() || token.empty())
		return (this->handleErrNeedMoreParams(c, "PASS") ,this->poolOut.push(c.getFd()), false);
	if (this->_password.size() != token.size() || !_constantTimeCheck(this->_password, token))
		return (this->handleErrPasswdMismatch(c) ,this->poolOut.push(c.getFd()), false);
	c.flagsLogin |= FLAG_CLIENT_PASS;
	return (true);
}
bool	Server::handlePing(Client &c, std::istringstream &iss) 
{
	std::string token;
	iss >> token;
	if (iss.fail() || token.empty())
		return (this->handleErrNeedMoreParams(c, "PING"), this->poolOut.push(c.getFd()), false);
	std::string	pongRet = ":";
	pongRet.append(this->_host).append(" PONG ").append(this->_host).append(" ").append(token).append("\r\n");
	this->sendToClient(c, pongRet);
	return (true);
}
bool	Server::handle_pong(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "pong: " << token << std::endl;
	return (true);
}
bool	Server::handlePrivMsg(Client &c, std::istringstream &iss) 
{
	std::string target, message;
	iss >> target;
	if (iss.fail() || target.empty())
		return (this->handleErrNoRecipient(c, "PRIVMSG"), this->poolOut.push(c.getFd()), false);
	std::getline(iss, message);
	if (message.empty())
		return (this->handleErrNotexttosend(c), this->poolOut.push(c.getFd()), false);
	size_t index = message.find_first_not_of(' ');
	if (index == std::string::npos || message[index] != ':')
		return (this->handleErrNotexttosend(c), this->poolOut.push(c.getFd()), false);

	std::vector<size_t>	clients;
	std::string realTarget(target);
	if (target[0] == '#')
	{
		target.erase(0, 1);
		Channel	*targetChannel = NULL;
		try {
			targetChannel = c.getChannel()[target].first;
		} catch (std::exception &e) {
			try {
				targetChannel = this->_channelTrie[target];
			} catch (std::exception &e) {
				return (this->handleErrNosuchchannel(c, target), this->poolOut.push(c.getFd()), false);
			}
			if (!targetChannel->checkMode(CHANNEL_NOT_EXTERNAL))
				return (this->handleErrCannotSendToChan(c, target), this->poolOut.push(c.getFd()), false);
		}
		if (targetChannel->checkMode(CHANNEL_MODERATED) && 
			!((c.checkFlag(target, CHANNEL_USER_OPERATOR) || c.checkFlag(target, CHANNEL_USER_VOICE))))
				return (this->handleErrCannotSendToChan(c, target), this->poolOut.push(c.getFd()), false);
		clients.assign(targetChannel->getClientsFD().begin(), targetChannel->getClientsFD().end());
	}
	else
	{
		size_t targetClient	= 0;
		try {
			targetClient = this->_clientTrie[target];
		} catch (std::exception &e) {
			return (this->handleErrNoSuchNick(c, target), this->poolOut.push(c.getFd()), false);
		}
		clients.push_back(targetClient);
		clients.push_back(c.getFd());
	}
	std::string		full(_formatBaseRelayMessage(c, "PRIVMSG"));
	message.erase(0, 1);
	full.append(target).append(1, ' ').append(message).append("\r\n");
	std::vector<size_t>::const_iterator end = clients.end();
	for (std::vector<size_t>::const_iterator it = clients.begin(); it != end; it++) {
		Client *curr = this->_clients[*it];
		if (!curr)
			continue ;
		this->sendToClient(*curr, full);
	}
	return (true);
}
bool	Server::handleQuit(Client &c, std::istringstream &iss) 
{
	std::string token;

	std::getline(iss, token);
	std::string message(":");
	message.append(c.getNick()).append(1, '!').append(c.getUserName()).append(1, '@').append(c.getHostName()).append(" QUIT :");
	if (token.empty())
		token += "Left without a message";
	if (token[0] == ':')
		token.erase(0, 1);
	token.append("\r\n");
	this->deconnectClient(c.getFd(), message + "Thanks for being with us\r\n", message + token);
	return (true);
}
bool	Server::handle_quote(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "quote: " << token << std::endl;
	return (true);
}
bool	Server::handle_rehash(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "rehash: " << token << std::endl;
	return (true);
}
bool	Server::handle_rules(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "rules: " << token << std::endl;
	return (true);
}
bool	Server::handle_server(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "server: " << token << std::endl;
	return (true);
}
bool	Server::handle_squery(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "squery: " << token << std::endl;
	return (true);
}
bool	Server::handle_squit(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "squit: " << token << std::endl;
	return (true);
}
bool	Server::handle_setname(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "setname: " << token << std::endl;
	return (true);
}
bool	Server::handle_silence(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "silence: " << token << std::endl;
	return (true);
}
bool	Server::handle_stats(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "stats: " << token << std::endl;
	return (true);
}
bool	Server::handle_summon(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "summon: " << token << std::endl;
	return (true);
}
bool	Server::handle_time(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "time: " << token << std::endl;
	return (true);
}
bool	Server::handle_topic(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "topic: " << token << std::endl;
	return (true);
}
bool	Server::handle_trace(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "trace: " << token << std::endl;
	return (true);
}
bool	Server::handleUser(Client &c, std::istringstream &iss) 
{

	if (!(c.flagsLogin & FLAG_CLIENT_PASS))
		return (this->handleErrNotregistered(c), this->poolOut.push(c.getFd()), false);
	if (c.flagsLogin & FLAG_CLIENT_USER)
		return (this->handleErrAlreadyRegistered(c), this->poolOut.push(c.getFd()), false);

	std::string userName, hostName, serverName, realName;
	if (!(iss >> userName >> hostName >> serverName)
		|| userName.empty() || hostName.empty() || serverName.empty())
		return (this->handleErrNeedMoreParams(c, "USER"), this->poolOut.push(c.getFd()), false);
	std::getline(iss, realName);
	if (realName.empty())
		return (this->handleErrNeedMoreParams(c, "USER"), this->poolOut.push(c.getFd()), false);
	size_t indexTrim = realName.find_first_not_of(' ');
	if (indexTrim == std::string::npos || realName[indexTrim] != ':')
		return (this->handleErrNeedMoreParams(c, "USER"), this->poolOut.push(c.getFd()), false);
	realName.erase(0, indexTrim + 1);
	if (userName.length() < 1 || hostName.length() < 1 || serverName.length() < 1 || realName.length() < 1)
		return (this->handleErrNeedMoreParams(c, "USER"), this->poolOut.push(c.getFd()), false);
	c.setUserName(userName);
	c.setHostName(hostName);
	c.setServerName(serverName);
	c.setRealName(realName);
	if (c.flagsLogin & FLAG_CLIENT_NICK)
	{
		this->_clientTrie.add(c.getNick(), c.getFd());
		this->_sendAllWelcome(c);
	}
	c.flagsLogin |= FLAG_CLIENT_USER;
	return (true);
}
bool	Server::handle_userhost(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "userhost: " << token << std::endl;
	return (true);
}
bool	Server::handle_userip(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "userip: " << token << std::endl;
	return (true);
}
bool	Server::handle_users(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "users: " << token << std::endl;
	return (true);
}
bool	Server::handle_version(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "version: " << token << std::endl;
	return (true);
}
bool	Server::handle_wallops(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "wallops: " << token << std::endl;
	return (true);
}
bool	Server::handle_watch(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "watch: " << token << std::endl;
	return (true);
}
bool	Server::handle_who(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "who: " << token << std::endl;
	return (true);
}
bool	Server::handle_whois(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "whois: " << token << std::endl;
	return (true);
}
bool	Server::handle_whowas(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "whowas: " << token << std::endl;
	return (true);
}
bool	Server::handleDcc(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "dcc: " << token << std::endl;
	return (true);
}
bool	Server::handle_message(Client &c, std::istringstream &iss) 
{
	(void)c;
	std::string token;
	iss >> token;
	std::cout << "In " << "message: " << token << std::endl;
	return (true);
}
