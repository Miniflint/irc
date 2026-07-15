#include "main.hpp"

void	serverReceivesLog(std::string msg) {
	size_t	endI = msg.find("\r\n");
	if (endI != std::string::npos)
		msg.erase(endI, endI + 2);
	std::cout << "\033[0;1;34m[Server receives] => \033[0;35m{ '\033[1m" << msg << "\033[0;35m' }\033[0m" << std::endl;
}

void	serverReceivesLogError(std::string msg, std::string error) {
	size_t	endI = msg.find("\r\n");
	if (endI != std::string::npos)
		msg.erase(endI, endI + 2);
	std::cout << "\033[0;1;34m[Server receives] => \033[31m[ERROR: " << error << "] => \033[0;33m{ '\033[1m" << msg << "\033[0;33m' }\033[0m" << std::endl;
}

void	serverSendsLog(std::string msg) {
	size_t	endI = msg.find("\r\n");
	if (endI != std::string::npos)
		msg.erase(endI, endI + 2);
	std::cout << "\033[0;1;32m[Server sends] => \033[0;36m{ '\033[1m" << msg << "\033[0;36m' }\033[0m" << std::endl;
}
