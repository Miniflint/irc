#include "Server.hpp"

std::string Server::handleRplWelcome(Client &c)
{
    std::string returnString(":Welcome the IRC Server of 42 (Made by Simon, Tricaducee and Miniflint) - ");
    const std::string &nickName = c.getNick();
    const std::string &userName = c.getUserName();
    const std::string &hostName = c.getHostName();
    returnString.reserve(returnString.size() + nickName.size() + userName.size() + hostName.size() + 5);
    return (returnString.append(nickName).append(1, '!').append(userName).append(1, '@').append(hostName).append("\r\n"));
}
std::string Server::handleRplYourhost(Client &c)
{
    (void)c;
    std::string returnString(":Your host is ");
    const std::string &hostName = this->getIp();
    returnString.reserve(returnString.size() + hostName.size() + 2);
    return (returnString.append(hostName).append("\r\n"));
}
std::string Server::handleRplCreated(Client &c)
{
    (void)c;
    return (":This server was created somewhere in history (We don't keep track of the date because of lazyness)\r\n");
}
std::string Server::handleRplMyinfo(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplBounce(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplTracelink(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplTraceconnecting(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplTracehandshake(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplTraceunknown(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplTraceoperator(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplTraceuser(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplTraceserver(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplTraceservice(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplTracenewtype(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplTraceclass(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplTracereconnect(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplStatslinkinfo(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplStatscommands(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplStatscline(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplStatsnline(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplStatsiline(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplStatskline(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplStatsqline(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplStatsyline(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplEndofstats(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplUmodeis(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplServiceinfo(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplEndofservices(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplService(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplServlist(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplServlistend(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplStatsvline(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplStatslline(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplStatsuptime(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplStatsoline(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplStatshline(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplStatsping(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplStatsbline(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplStatsdline(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplLuserclient(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplLuserop(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplLuserunknown(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplLuserchannels(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplLuserme(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplAdminme(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplAdminloc1(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplAdminloc2(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplAdminemail(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplTracelog(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplTraceend(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplTryagain(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplNone(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplAway(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplUserhost(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplIson(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplUnaway(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplNowaway(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplWhoisuser(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplWhoisserver(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplWhoisoperator(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplWhowasuser(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplEndofwho(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplWhoischanop(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplWhoisidle(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplEndofwhois(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplWhoischannels(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplListstart(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplList(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplListend(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplChannelmodeis(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplUniqopis(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplNotopic(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplTopic(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplInviting(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplSummoning(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplInvitelist(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplEndofinvitelist(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplExceptlist(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplEndofexceptlist(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplVersion(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplWhoreply(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplNamreply(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplKilldone(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplClosing(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplCloseend(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplLinks(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplEndoflinks(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplEndofnames(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplBanlist(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplEndofbanlist(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplEndofwhowas(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplInfo(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplMotd(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplInfostart(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplEndofinfo(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplMotdstart(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplEndofmotd(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplYoureoper(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplRehashing(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplYoureservice(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplMyportis(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplTime(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplUsersstart(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplUsers(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplEndofusers(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleRplNousers(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNosuchnick(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNosuchserver(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNosuchchannel(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrCannotsendtochan(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrToomanychannels(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrWasnosuchnick(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrToomanytargets(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNosuchservice(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNoorigin(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNorecipient(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNotexttosend(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNotoplevel(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrWildtoplevel(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrBadmask(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrUnknowncommand(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNomotd(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNoadmininfo(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrFileerror(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNonicknamegiven(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrErroneusnickname(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNicknameinuse(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNickcollision(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrUnavailresource(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrUsernotinchannel(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNotonchannel(Client &c)
{
    (void)c;
    // uint32_t t = ERR_NOTONCHANNEL;
    return (":Channel or Client does not exist\r\n");
}
std::string Server::handleErrUseronchannel(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNologin(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrSummondisabled(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrUsersdisabled(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNotregistered(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNeedmoreparams(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrAlreadyregistered(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNopermforhost(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrPasswdmismatch(Client &c)
{
    (void)c;
    return (":Password does not match the actual password\r\n");
}
std::string Server::handleErrYourebannedcreep(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrYouwillbebanned(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrKeyset(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrChannelisfull(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrUnknownmode(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrInviteonlychan(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrBannedfromchan(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrBadchannelkey(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrBadchanmask(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNochanmodes(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrBanlistfull(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNoprivileges(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrChanoprivsneeded(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrCantkillserver(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrRestricted(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrUniqoprivsneeded(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNooperhost(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrNoservicehost(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrUmodeunknownflag(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
std::string Server::handleErrUsersdontmatch(Client &c)
{
    (void)c;
    return ("Not implemented yet");
}
