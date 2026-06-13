#include "main.hpp"

int	main(int ac, char **argv)
{
	if (ac != 3)
		return (1);
	std::cout << argv[0] << " " << argv[1] << " " << argv[2] << std::endl;
	return (0);
}