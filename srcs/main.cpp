#include "main.hpp"

# include <stdlib.h>
# include <ostream>
# include <csignal>

// int	key_print(std::string word)
// {
// 	std::ostream << word;
// }

# include <iostream>
# include <string>

void	tag() {
	std::cout << "--------------------------------------------------------------------------" << std::endl;
	std::cout << "|  /$$   /$$  /$$$$$$  /$$$$$$ /$$$$$$$   /$$$$$$  | 42 Project ft_irc   |" << std::endl;
	std::cout << "| | $$  | $$ /$$__  $$|_  $$_/| $$__  $$ /$$__  $$ | With love by:       |" << std::endl;
	std::cout << "| | $$  | $$|__/  \\ $$  | $$  | $$  \\ $$| $$  \\__/ | - Miniflint         |" << std::endl;
	std::cout << "| | $$$$$$$$  /$$$$$$/  | $$  | $$$$$$$/| $$       | - Simon             |" << std::endl;
	std::cout << "| |_____  $$ /$$____/   | $$  | $$__  $$| $$       | - and Tricaducee    |" << std::endl;
	std::cout << "|       | $$| $$        | $$  | $$  \\ $$| $$    $$ | Tested with:        |" << std::endl;
	std::cout << "|       | $$| $$$$$$$$ /$$$$$$| $$  | $$|  $$$$$$/ | Halloy irc client   |" << std::endl;
	std::cout << "|       |__/|________/|______/|__/  |__/ \\______/  | https://halloy.chat |" << std::endl;
	std::cout << "--------------------------------------------------------------------------" << std::endl;                                         
}

void	display_help(char *filename)
{
	std::cout << filename << " <port> <password>" << std::endl;
	std::cout << "<port> must be a postive integer > 3" << std::endl;
	std::cout << "<password> must be at least 2 chars" << std::endl;
	std::cout << "options: \n\t" << "-h, --help: Display this page" << std::endl;
	std::cout << "\t" << "-o, --output: set the output file for the graph" << std::endl;
}

int	parse_av(int ac, char **argv)
{
	if (ac < 2)
		return ((std::cout << argv[0] << " <port> <password>" << std::endl), 2);
	std::string av(argv[1]);
	if (ac == 2 && (av == "--help" || av == "-h"))
		return (display_help(argv[0]), 1);
	return (0);
}
/* 
void	createUserAndRegister(Server &serv, size_t fd, std::string first, std::string sec)
{
	serv.setClient(fd);
	serv.getClient(fd).buffer = first + "\r\n";
	(void)serv.doCommand(fd);
	serv.getClient(fd).buffer = sec + "\r\n";
	(void)serv.doCommand(fd);
}
*/ 
int	main(int ac, char **argv)
{
	unsigned int i = parse_av(ac, argv);
	if (i >= 1)
		return (i - 1);
	std::istringstream iss(argv[1]);
	int	port;
	iss >> port;
	if (iss.fail())
		return (std::cerr << "Error parsing the port" << std::endl, 1);
	if (std::string(argv[2]).length() < 2 || port <= 3)
		return (display_help(argv[0]), 1);
	Server	serv(port, argv[2]);
	tag();
	do {
		serv.run();
		if (serv.runStatus == RUN_SHUTDOWN)
			std::cout << "\033[1;31m!!! => [Server: Shutdown]\033[0m" << std::endl;
		else
			std::cout << "\033[1;33m!!! => [Server: Restart]\033[0m" << std::endl;
	} while (serv.runStatus != RUN_SHUTDOWN);
	//serv.setClient(0);
	//createUserAndRegister(serv, 5, "NICK Xavier", "USER Xav * * :Dup");
	//createUserAndRegister(serv, 0, "NICK amy", "USER am * * :dupdup");
	//while (1)
	//{
	//	std::cout << "Enter your command: ";
	//	std::string input;
	//	std::getline(std::cin, input);
	//	serv.getClient(0).buffer = input + "\r\n";
	//	(void)serv.doCommand(0);
	//	std::cout << std::endl;
	//}
	return (0);
}
