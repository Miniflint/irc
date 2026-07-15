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
std::cout << "| | $$  | $$ /$$__  $$|_  $$_/| $$__  $$ /$$__  $$ | Whith love by:      |" << std::endl;
std::cout << "| | $$  | $$|__/  \\ $$  | $$  | $$  \\ $$| $$  \\__/ | - Miniflint         |" << std::endl;
std::cout << "| | $$$$$$$$  /$$$$$$/  | $$  | $$$$$$$/| $$       | - Simon             |" << std::endl;
std::cout << "| |_____  $$ /$$____/   | $$  | $$__  $$| $$       | - and Tricaducee    |" << std::endl;
std::cout << "|       | $$| $$        | $$  | $$  \\ $$| $$    $$ | Tested whith:       |" << std::endl;
std::cout << "|       | $$| $$$$$$$$ /$$$$$$| $$  | $$|  $$$$$$/ | Halloy irc client   |" << std::endl;
std::cout << "|       |__/|________/|______/|__/  |__/ \\______/  | https://halloy.chat |" << std::endl;
std::cout << "--------------------------------------------------------------------------" << std::endl;                                         
}

void	display_help(char *filename)
{
	std::cout << filename << " <port> <password>" << std::endl;
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
	Server	serv(atoi(argv[1]), argv[2]);
	tag();
	serv.run();
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
