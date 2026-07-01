#include "main.hpp"

# include <stdlib.h>
# include <ostream>

// int	key_print(std::string word)
// {
// 	std::ostream << word;
// }

# include <iostream>
# include <string>

void	display_help(char *filename)
{
	std::cout << filename << " <port> <password>" << std::endl;
	std::cout << "options: \n\t" << "-h, --help: Display this page" << std::endl;
	std::cout << "\t" << "-o, --output: set the output file for the graph" << std::endl;
}

int	parse_av(int ac, char **argv)
{
	std::string av(argv[1]);
	if (ac == 2 && (av == "--help" || av == "-h"))
		return (display_help(argv[0]), 1);
	if (ac == 3)
		return (0);
	if (ac > 3)
		return (0);
	else
		return (std::cout << argv[0] << " <port> <password>" << std::endl, 2);
	return (2);
}

int	main(int ac, char **argv)
{
	unsigned int i = parse_av(ac, argv);
	if (i == 1)
		return (0);
	else if (i > 1)
		return (1);
	Server	serv(atoi(argv[1]), argv[2]);
	std::string arg(argv[3]);
	std::string rest(argv[4]);
	serv.do_command(5, arg, rest);
	return (0);
}
