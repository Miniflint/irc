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
"462 ERR_ALREADYREGISTRED : sent when the client sends USER after registration is already complete",};
		return (HelpTextVectorMaker(lines, 8));
}
