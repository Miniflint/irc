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
"The second and third parameter of the command should be '0' and '*'. the meaning of these two parameter varies between version of the irc protocol",
"The realname parameter starts with a colon, meaning everything after it, including spaces, is treated as a single parameter.",
"This command must be sent as part of the registration process, along with NICK.",
"461 ERR_NEEDMOREPARAMS : sent when the number of parameters given is less than 4",
"462 ERR_ALREADYREGISTRED : sent when the client sends USER after registration is already complete"};
	return (HelpTextVectorMaker(lines, 7));
}

std::vector<std::string>	Server::helpJoin(void) {
	const char	*lines[] = {"JOIN <channel>{,<channel>} [<key>{,<key>}]",
"The JOIN command is used to make a client join specific channel(s).",
"If the channel does not exist, it is created and the client automatically becomes a founder and an operator.",
"If the channel has a key set, the client must provide the matching key to join.",
"On success, the JOIN message itself is echoed back to the client, with the channel as its first parameter",
"332 RPL_TOPIC : sent after a successful join if the channel has a topic set",
"331 RPL_NOTOPIC : sent after a successful join if the channel has no topic set",
"353 RPL_NAMREPLY : sent one or more times after a successful join, listing the channel members",
"366 RPL_ENDOFNAMES : sent once after all RPL_NAMREPLY lines, to indicate the end of the list",
"461 ERR_NEEDMOREPARAMS : sent when no channel parameter is given",
"471 ERR_CHANNELISFULL : sent when the channel has reached its user limit",
"473 ERR_INVITEONLYCHAN : sent when the channel is invite-only and the client has not been invited",
"474 ERR_BANNEDFROMCHAN : sent when the client is banned from the channel",
"475 ERR_BADCHANNELKEY : sent when the key provided does not match the channel key",
"476 ERR_BADCHANMASK : sent when the channel name does not start with a valid channel prefix",
"479 ERR_BADCHANNAME : sent when the channel name exceeds the maximum allowed length"};
		return (HelpTextVectorMaker(lines, 16));
}

std::vector<std::string>	Server::helpInvite(void) {
	const char	*lines[] = {"INVITE <nickname> <channel>",
"The INVITE command is used to invite a user to a channel.",
"Half-Operator privileges is required to invite if the channel is invite-only.",
"401 ERR_NOSUCHNICK : sent when the target nickname does not exist",
"403 ERR_NOSUCHCHANNEL : sent when the channel name does not exist",
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
"The message text can starts with a colon. if it does, everything after it, including spaces, is treated as a single parameter.",
"If it does not, only the first word will be taken",
"401 ERR_NOSUCHNICK : sent when the target nickname does not exist",
"403 ERR_NOSUCHCHANNEL : sent when the target channel does not exist",
"404 ERR_CANNOTSENDTOCHAN : sent when the client cannot send a message to the channel",
"411 ERR_NORECIPIENT : sent when no target is given",
"412 ERR_NOTEXTTOSEND : sent when no message text is given"};
	return (HelpTextVectorMaker(lines, 9));
}

std::vector<std::string>	Server::helpMode(void) {
	const char	*lines[] = {"MODE <target> <modes> [<mode parameters>]",
"The MODE command is used to change or view the modes of a channel, or the modes of a user.",
"For channels, the following modes are supported:",
"i (Invite-only) : only invited clients can join the channel",
"s (Secret) : hides the channel from LIST/NAMES results for non-members",
"m (Moderated) : only members with +v or higher can speak",
"n (No external messages) : a client outside the channel cannot send it a message",
"t (Topic protection) : only members with +h or higher can change the topic",
"k (Key) : sets a password required to join the channel",
"l (User limit) : sets the maximum number of members allowed",
"b (Ban) : prevents a banned client from joining the channel",
"The following privilege modes can be set on a channel member (MODE #channel +/-x <nick>):",
"v (Voice) : allows the user to speak in a moderated (+m) channel",
"h (Half-operator) : minimum level required to change a protected topic and see invisible users via WHO",
"o (Operator) : full access to KICK, TOPIC, MODE and INVITE on the channel",
"a (Protected) : same as operator, but cannot be kicked by an operator",
"The following modes can be set on a user (MODE <nick> +/-x):",
"i (Invisible) : hides the client from generic WHO results",
"x (Hidden) : mask the real ip address",
"d (Deaf) : block messages from channels",
"R (Registered) : block private messages",
"g (Registered) : block private messages from whom you haven't sent message yet",
"B (Bot) : indicate that the user is a bot / cannot remove once added",
"o/O (Server operator) : grants KICK/MODE/TOPIC/INVITE/WHO access and bypasses channel restrictions",
"a/A (Server admin) : protects the user from being KILLed by a simple operator",
"324 RPL_CHANNELMODEIS : sent to reply with the current modes of a channel",
"221 RPL_UMODEIS : sent to reply with the current modes of a user",
"401 ERR_NOSUCHNICK : sent when a target nickname given as a mode parameter does not exist",
"403 ERR_NOSUCHCHANNEL : sent when the channel does not exist",
"442 ERR_NOTONCHANNEL : sent when the client is not on the channel",
"461 ERR_NEEDMOREPARAMS : sent when a mode requiring a parameter is given without one",
"467 ERR_KEYSET : sent when trying to set a key on a channel that already has one",
"472 ERR_UNKNOWNMODE : sent when an unsupported mode character is given",
"477 ERR_NOCHANMODES : sent when the channel does not support modes",
"482 ERR_CHANOPRIVSNEEDED : sent when the client is not a channel operator",
"501 ERR_UMODEUNKNOWNFLAG : sent when an unsupported user mode character is given",
"502 ERR_USERSDONTMATCH : sent when a client tries to change the mode of another user"};
	return (HelpTextVectorMaker(lines, 37));
}

std::vector<std::string>	Server::helpTopic(void) {
	const char	*lines[] = {"TOPIC <channel> [<topic>]",
"The TOPIC command is used to view or change the topic of a channel.",
"If no topic parameter is given, the current topic is returned.",
"If the channel has topic protection (+t) set, only a channel operator or higher can change the topic.",
"331 RPL_NOTOPIC : sent when the channel has no topic set",
"332 RPL_TOPIC : sent with the current topic when it is requested",
"403 ERR_NOSUCHCHANNEL : sent when the channel does not exist",
"442 ERR_NOTONCHANNEL : sent when the client is not on the channel",
"461 ERR_NEEDMOREPARAMS : sent when no channel parameter is given",
"482 ERR_CHANOPRIVSNEEDED : sent when the client tries to change the topic without the required privilege"};
	return (HelpTextVectorMaker(lines, 10));
}

std::vector<std::string>	Server::helpKick(void) {
	const char	*lines[] = {"KICK <channel> <nickname> [<comment>]",
"The KICK command is used to remove a client from a channel.",
"Channel operator or higher can kick a member from the channel.",
"Server operator or higher can kick a member from the channel.",
"401 ERR_NOSUCHNICK : sent when the target nickname does not exist",
"403 ERR_NOSUCHCHANNEL : sent when the channel does not exist",
"441 ERR_USERNOTINCHANNEL : sent when the target user is not on the channel",
"442 ERR_NOTONCHANNEL : sent when the client sending the command is not on the channel",
"461 ERR_NEEDMOREPARAMS : sent when the number of parameters given is less than 2",
"482 ERR_CHANOPRIVSNEEDED : sent when the client is not a channel operator"};
	return (HelpTextVectorMaker(lines, 10));
}

std::vector<std::string>	Server::helpQuit(void) {
	const char	*lines[] = {"QUIT [<message>]",
"The QUIT command is used to terminate the client's connection to the server.",
"If a message is given, it is sent to other users as the reason for leaving.",
"The server closes the connection after processing this command.",
"Numeric Replies: none"};
	return (HelpTextVectorMaker(lines, 5));
}

std::vector<std::string>	Server::helpPart(void) {
	const char	*lines[] = {"PART <channel>{,<channel>} [<message>]",
"The PART command is used to leave one or more channels.",
"If a message is given, it is sent to other channel members as the reason for leaving.",
"403 ERR_NOSUCHCHANNEL : sent when the channel does not exist",
"442 ERR_NOTONCHANNEL : sent when the client is not on the channel",
"461 ERR_NEEDMOREPARAMS : sent when no channel parameter is given"};
	return (HelpTextVectorMaker(lines, 6));
}

std::vector<std::string>	Server::helpPing(void) {
	const char	*lines[] = {"PING",
"The PING command is used to test the presence of an active connection.",
"The recipient must reply with a PONG command echoing the same parameter.",
"409 ERR_NOORIGIN : sent when no origin parameter is given"};
	return (HelpTextVectorMaker(lines, 4));
}

std::vector<std::string>	Server::helpKill(void) {
	const char	*lines[] = {"KILL <nickname> <comment>",
"The KILL command is used to forcibly disconnect a client from the server.",
"Only a server operator or higher can use this command.",
"401 ERR_NOSUCHNICK : sent when the target nickname does not exist",
"461 ERR_NEEDMOREPARAMS : sent when the number of parameters given is less than 2",
"481 ERR_NOPRIVILEGES : sent when the client is not a server operator",
"483 ERR_CANTKILLSERVER : sent when the client tries to kill a server connection"};
	return (HelpTextVectorMaker(lines, 7));
}

std::vector<std::string>	Server::helpDie(void) {
	const char	*lines[] = {"DIE",
"The DIE command is used to shut down the server.",
"Only a server operator or higher can use this command.",
"481 ERR_NOPRIVILEGES : sent when the client is not a server operator"};
	return (HelpTextVectorMaker(lines, 4));
}

std::vector<std::string>	Server::helpRestart(void) {
	const char	*lines[] = {"RESTART",
"The RESTART command is used to restart the server.",
"Only a server operator or higher can use this command.",
"481 ERR_NOPRIVILEGES : sent when the client is not a server operator"};
	return (HelpTextVectorMaker(lines, 4));
}

std::vector<std::string>	Server::helpInfo(void) {
	const char	*lines[] = {"INFO",
"The INFO command is used to return information describing the server.",
"371 RPL_INFO : sent for each line of information about the server",
"374 RPL_ENDOFINFO : sent to indicate the end of the INFO reply"};
	return (HelpTextVectorMaker(lines, 4));
}

std::vector<std::string>	Server::helpWho(void) {
	const char	*lines[] = {"WHO <channel>",
"The WHO command is used to list the users currently on a channel.",
"The parameter must be the exact name of an existing channel, no wildcard or pattern matching is supported.",
"WHO only works for channels in this server, searching by nickname is not implemented.",
"352 RPL_WHOREPLY : sent for each user matching the request",
"315 RPL_ENDOFWHO : sent to indicate the end of the WHO reply, whether or not any results were found",
"461 ERR_NEEDMOREPARAMS : sent when no channel parameter is given"};
		return (HelpTextVectorMaker(lines, 7));
}

std::vector<std::string>	Server::helpAway(void) {
	const char	*lines[] = {"AWAY [<message>]",
"The AWAY command sets or clears your away status.",
"With a message: you are marked as away, and that message is shown",
"automatically to anyone who sends you a PRIVMSG while you're away.",
"Without a message: your away status is cleared.",
"305 RPL_UNAWAY : you are no longer marked as away",
"306 RPL_NOWAWAY : you are now marked as away",
"301 RPL_AWAY : sent to a client attempting to message you, showing your away message"};
	return (HelpTextVectorMaker(lines, 8));
}

std::vector<std::string>	Server::helpOper(void) {
	const char	*lines[] = {"OPER <login> <password>",
"The OPER command allow a user to become server operator or admin.",
"381 RPL_YOUREOPER : sent to a client after a successful OPER command.",
"461 ERR_NEEDMOREPARAMS : sent when the number of params is less than 2.",
"464 ERR_PASSWDMISMATCH : sent when the password does not match with db password.",
"491 ERR_NOOPERHOST : sent when OPER command failed because server does not allow attempts from this host."};
	return (HelpTextVectorMaker(lines, 6));
}

std::vector<std::string>	Server::helpCap(void) {
	const char	*lines[] = {"CAP <subcommand>",
"The CAP command is used for capability negotiation between a server and a client.",
"<subcommand>: LS <version>: discover the available capabilities on this server with a particular version",
"<subcommand>: LS: wait till the end of registration to display capabilities",
"<subcommand>: REQ :<cap> - request capability or capabilities",
"<subcommand>: REQ * ACK: capability or capabilities are taken into account.",
"<subcommand>: REQ * NAK: capability or capabilities could not be taken into account.",
"<subcommand>: END: end of transaction.",
"For more information. visit https://ircv3.net/specs/extensions/capability-negotiation.html."};
	return (HelpTextVectorMaker(lines, 9));
}

/*

std::vector<std::string>	Server::help(void) {
	const char	*lines[] = {};
		return (HelpTextVectorMaker(lines, ));
}
*/
