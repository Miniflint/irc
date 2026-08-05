#include "Server.hpp"

static std::vector<std::string>	HelpTextVectorMaker(const char *lines[], size_t n) {
	return std::vector<std::string>(lines, lines + n);
}

std::vector<std::string>	Server::HelpNick(void) {
	const char	*lines[] = {"NICK <nickname>", "The NICK command is used to give the client a nickname or change the previous one.", "Numeric Replies: 431, 433, 436"};
		return (HelpTextVectorMaker(lines, 3);
}

