#include "Server.hpp"

static std::vector<std::string>	HelpTextVectorMaker(const char *lines[], size_t n) {
	return std::vector<std::string>(lines, lines + n);
}

std::vector<std::string>	Server::helpNick(void) {
	const char	*lines[] = {"NICK <nickname>",
	"The NICK command is used to give the client a nickname or change the previous one.",
	"Numeric Replies: 431, 433, 436"};
		return (HelpTextVectorMaker(lines, 3));
}

std::vector<std::string>	Server::helpPass(void) {
	const char	*lines[] = {"PASS <password>",
	"The PASS command is used to set a ‘connection password’. If set, the password must be set before",
	"any attempt to register the connection is made. This requires that clients send a PASS command",
	"before sending the NICK / USER combination.", "Numeric Replies: 461, 462, 464"};
		return (HelpTextVectorMaker(lines, 5));
}

std::vector<std::string>	Server::helpUser(void) {
	const char	*lines[] = {"USER <username> 0 * <realname>",
	"The USER command is used at the beginning of a connection to specify the username and realname",
	"of a new user",
	"It must be noted that <realname> must be the last parameter because it may contain SPACE (' ',", "0x20) characters, and should be prefixed with a colon (:) if required.",
	"Numeric Replies: 461, 462"};
		return (HelpTextVectorMaker(lines, 3));
}
