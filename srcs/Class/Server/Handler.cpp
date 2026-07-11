#include "Server.hpp"

static bool _checkClientExist(Trie<Client> &trie, const std::string &toCheck)
{
    try {
        (void)trie[toCheck];
    } catch (std::exception &e) {
        return (true);
    }
    return (false);
}

bool Server::handle_admin(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "admin: " << token << std::endl;
    return (true);
}
bool Server::handle_away(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "away: " << token << std::endl;
    return (true);
}
bool Server::handle_cnotice(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "cnotice: " << token << std::endl;
    return (true);
}
bool Server::handle_cprivmsg(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "cprivmsg: " << token << std::endl;
    return (true);
}
bool Server::handle_connect(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "connect: " << token << std::endl;
    return (true);
}
bool Server::handle_die(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "die: " << token << std::endl;
    return (true);
}
bool Server::handle_error(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "error: " << token << std::endl;
    return (true);
}
bool Server::handle_help(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "help: " << token << std::endl;
    return (true);
}
bool Server::handle_info(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "info: " << token << std::endl;
    return (true);
}
bool Server::handle_invite(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "invite: " << token << std::endl;
    return (true);
}
bool Server::handle_ison(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "ison: " << token << std::endl;
    return (true);
}
bool Server::handle_join(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "join: " << token << std::endl;
    return (true);
}
bool Server::handle_kick(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "kick: " << token << std::endl;
    return (true);
}
bool Server::handle_kill(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "kill: " << token << std::endl;
    return (true);
}
bool Server::handle_knock(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "knock: " << token << std::endl;
    return (true);
}
bool Server::handle_links(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "links: " << token << std::endl;
    return (true);
}
bool Server::handle_list(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "list: " << token << std::endl;
    return (true);
}
bool Server::handle_lusers(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "lusers: " << token << std::endl;
    return (true);
}
bool Server::handle_mode(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "mode: " << token << std::endl;
    return (true);
}
bool Server::handle_motd(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "motd: " << token << std::endl;
    return (true);
}
bool Server::handle_names(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "names: " << token << std::endl;
    return (true);
}
bool Server::handleNick(Client &c, std::istringstream &iss) 
{
    std::string token;

    iss >> token >> std::noskipws;
    if (iss.fail())
        return (std::cerr << "[ERROR]: istringstream formatting error" << std::endl, false);
    if (token.empty() || token.length() > 9)
        return (std::cerr << "[ERROR]: Invalid nickname" << std::endl, false);
    if (!_checkClientExist(this->_userNickname, token))
        return (std::cerr << "[ERROR]: User Already exist" << std::endl, false);
    std::string old_username(c.getNick());
    if (!_checkClientExist(this->_userNickname, old_username))
    {
        std::cout << "[SUCCESS]: Deleting into trie (nickName)" << std::endl;
        this->_userNickname.del(old_username);
    }
    c.setNick(token);
    if (!c.getUserName().empty())
    {
        std::cout << "[SUCCESS]: Adding to trie (nickName)" << std::endl;
        this->_userNickname.add(token, c);
    }
    std::cout << "[SUCCESS]: Changing nickname - " << token << std::endl;
    return (true);
}
bool Server::handle_notice(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "notice: " << token << std::endl;
    return (true);
}
bool Server::handle_oper(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "oper: " << token << std::endl;
    return (true);
}
bool Server::handle_part(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "part: " << token << std::endl;
    return (true);
}
bool Server::handle_pass(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "pass: " << token << std::endl;
    return (true);
}
bool Server::handle_ping(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "ping: " << token << std::endl;
    return (true);
}
bool Server::handle_pong(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "pong: " << token << std::endl;
    return (true);
}
bool Server::handle_privmsg(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "privmsg: " << token << std::endl;
    return (true);
}
bool Server::handle_quit(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "quit: " << token << std::endl;
    return (true);
}
bool Server::handle_quote(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "quote: " << token << std::endl;
    return (true);
}
bool Server::handle_rehash(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "rehash: " << token << std::endl;
    return (true);
}
bool Server::handle_rules(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "rules: " << token << std::endl;
    return (true);
}
bool Server::handle_server(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "server: " << token << std::endl;
    return (true);
}
bool Server::handle_squery(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "squery: " << token << std::endl;
    return (true);
}
bool Server::handle_squit(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "squit: " << token << std::endl;
    return (true);
}
bool Server::handle_setname(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "setname: " << token << std::endl;
    return (true);
}
bool Server::handle_silence(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "silence: " << token << std::endl;
    return (true);
}
bool Server::handle_stats(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "stats: " << token << std::endl;
    return (true);
}
bool Server::handle_summon(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "summon: " << token << std::endl;
    return (true);
}
bool Server::handle_time(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "time: " << token << std::endl;
    return (true);
}
bool Server::handle_topic(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "topic: " << token << std::endl;
    return (true);
}
bool Server::handle_trace(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "trace: " << token << std::endl;
    return (true);
}
bool Server::handleUser(Client &c, std::istringstream &iss) 
{
    if (!c.getUserName().empty() || !c.getHostName().empty() ||
        !c.getServerName().empty() || !c.getRealName().empty())
        return (std::cerr << "[ERROR]: already has USER" << std::endl, false);

    std::string userName, hostName, serverName, realName;
    if (!(iss >> userName >> hostName >> serverName) || iss.fail())
        return (std::cerr << "[ERROR]: istringstream parsing failed" << std::endl, false);
    std::getline(iss, realName, '\r');
    if (realName.empty())
        return (std::cerr << "[ERROR]: empty nickname" << std::endl, false);
    size_t indexTrim = realName.find_first_not_of(' ');
    if (indexTrim == std::string::npos || realName[indexTrim] != ':')
        return (std::cerr << "[ERROR]: problem parsing realName" << std::endl, false);
    realName.erase(0, indexTrim + 1);
    if (userName.length() < 1 || hostName.length() < 1 || serverName.length() < 1)
        return (std::cerr << "[ERROR]: problem parsing" << std::endl, false);
    c.setUserName(userName);
    c.setHostName(hostName);
    c.setServerName(serverName);
    c.setRealName(realName);
    const std::string &nickName(c.getNick());
    if (!nickName.empty() && _checkClientExist(this->_userNickname, nickName))
    {
        std::cout << "[SUCCESS]: Adding to trie (nickName) - " << nickName << std::endl;
        this->_userNickname.add(nickName, c);
    }
    std::cout << "[SUCCESS]: Setting userName - " << userName << std::endl;
    std::cout << "[SUCCESS]: Setting hostName - " << hostName << std::endl;
    std::cout << "[SUCCESS]: Setting serverName - " << serverName << std::endl;
    std::cout << "[SUCCESS]: Setting realName - " << realName << std::endl;
    return (true);
}
bool Server::handle_userhost(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "userhost: " << token << std::endl;
    return (true);
}
bool Server::handle_userip(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "userip: " << token << std::endl;
    return (true);
}
bool Server::handle_users(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "users: " << token << std::endl;
    return (true);
}
bool Server::handle_version(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "version: " << token << std::endl;
    return (true);
}
bool Server::handle_wallops(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "wallops: " << token << std::endl;
    return (true);
}
bool Server::handle_watch(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "watch: " << token << std::endl;
    return (true);
}
bool Server::handle_who(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "who: " << token << std::endl;
    return (true);
}
bool Server::handle_whois(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "whois: " << token << std::endl;
    return (true);
}
bool Server::handle_whowas(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "whowas: " << token << std::endl;
    return (true);
}
bool Server::handleDcc(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "dcc: " << token << std::endl;
    return (true);
}
bool Server::handle_message(Client &c, std::istringstream &iss) 
{
    (void)c;
    std::string token;
    iss >> token;
    std::cout << "In " << "message: " << token << std::endl;
    return (true);
}