#include "Server.hpp"

static std::vector<std::string>	HelpTextVectorMaker(const char *lines[], size_t n) {
	return std::vector<std::string>(lines, lines + n);
}

std::vector<std::string>	Server::helpNick(void) {
	const char	*lines[] = {"NICK <nickname>",
"The NICK command is used to give the client a nickname or change the previous one.",
"431 ERR_NONICKNAMEGIVEN : sent when no nickname parameter is given",
"432 ERR_ERRONEUSNICKNAME : sent when the nickname contains invalid characters",
"433 ERR_NICKNAMEINUSE : sent when the requested nickname is already in use",
"436 ERR_NICKCOLLISION : sent when a nickname collision is detected during registration"};
		return (HelpTextVectorMaker(lines, 6));
}

std::vector<std::string>	Server::helpPass(void) {
	const char	*lines[] = {"PASS <password>",
"The PASS command is used to set a connection password before registration.",
"This command must be sent before the NICK/USER registration commands.",
"461 ERR_NEEDMOREPARAMS : sent when no password parameter is given",
"462 ERR_ALREADYREGISTRED : sent when the client sends PASS after registration is already complete",
"464 ERR_PASSWDMISMATCH : sent when the password provided does not match the server password"};
		return (HelpTextVectorMaker(lines, 6));
}

std::vector<std::string>	Server::helpUser(void) {
	const char	*lines[] = {"USER <username> 0 * :<realname>",
"The USER command is used to specify the username and realname of a new user during registration.",
"The mode parameter is unused in this server and should always be set to 0.",
"The unused parameter should always be set to *.",
"The realname parameter starts with a colon, meaning everything after it, including spaces, is treated as a single parameter.",
"This command must be sent as part of the registration process, along with NICK.",
"461 ERR_NEEDMOREPARAMS : sent when the number of parameters given is less than 4",
"462 ERR_ALREADYREGISTRED : sent when the client sends USER after registration is already complete"};
		return (HelpTextVectorMaker(lines, 8));
}

std::vector<std::string>	Server::helpJoin(void) {
	const char	*lines[] = {"JOIN <channel>{,<channel>} [<key>{,<key>}]",
"The JOIN command is used to make a client start listening on a specific channel.",
"If the channel does not exist, it is created and the client automatically becomes an operator.",
"If the channel has a key set, the client must provide the matching key to join.",
"461 ERR_NEEDMOREPARAMS : sent when no channel parameter is given",
"403 ERR_NOSUCHCHANNEL : sent when the channel name is invalid",
"405 ERR_TOOMANYCHANNELS : sent when the client has already joined the maximum allowed number of channels",
"471 ERR_CHANNELISFULL : sent when the channel has reached its user limit",
"473 ERR_INVITEONLYCHAN : sent when the channel is invite-only and the client has not been invited",
"474 ERR_BANNEDFROMCHAN : sent when the client is banned from the channel",
"475 ERR_BADCHANNELKEY : sent when the key provided does not match the channel key",
"476 ERR_BADCHANMASK : sent when the channel name does not respect the expected format"};
		return (HelpTextVectorMaker(lines, 12));
}

std::vector<std::string>	Server::helpInvite(void) {
	const char	*lines[] = {"INVITE <nickname> <channel>",
"The INVITE command is used to invite a user to a channel.",
"Only a channel operator can invite users if the channel is invite-only.",
"401 ERR_NOSUCHNICK : sent when the target nickname does not exist",
"442 ERR_NOTONCHANNEL : sent when the client sending the command is not on the channel",
"443 ERR_USERONCHANNEL : sent when the invited user is already on the channel",
"461 ERR_NEEDMOREPARAMS : sent when the number of parameters given is less than 2",
"482 ERR_CHANOPRIVSNEEDED : sent when the client is not a channel operator on an invite-only channel",
"341 RPL_INVITING : sent to confirm the invite was successfully sent"};
		return (HelpTextVectorMaker(lines, 9));
}

std::vector<std::string>	Server::helpPrivmsg(void) {
	const char	*lines[] = {"PRIVMSG <target>{,<target>} <text to be sent>",
"The PRIVMSG command is used to send a private message to a user or a channel.",
"The message text starts with a colon, meaning everything after it, including spaces, is treated as a single parameter.",
"401 ERR_NOSUCHNICK : sent when the target nickname does not exist",
"403 ERR_NOSUCHCHANNEL : sent when the target channel does not exist",
"404 ERR_CANNOTSENDTOCHAN : sent when the client cannot send a message to the channel",
"411 ERR_NORECIPIENT : sent when no target is given",
"412 ERR_NOTEXTTOSEND : sent when no message text is given"};
		return (HelpTextVectorMaker(lines, 8));
}



/*

std::vector<std::string>	Server::help(void) {
	const char	*lines[] = {};
		return (HelpTextVectorMaker(lines, 12));
}
*/
