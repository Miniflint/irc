#include "main.hpp"

# include <stdlib.h>
# include <ostream>

// int	key_print(std::string word)
// {
// 	std::ostream << word;
// }

int	main(int ac, char **argv)
{
	if (ac != 2)
		return (1);
	std::string	key_list[] = {"penis", "pen", "apple", "applic", "application", "fete",
		"fetard", "felation", "fee", "coupe", "coupable", "culpabilite"};
	
	(void)argv;
	Trie<int>	test_multi;
	//test_multi.add("raq", 0);
	//test_multi.add("ratisser", 2);
	//test_multi.add("ratackckckck", 2);
	//test_multi.create_graph();
	int	i = 0;
	while (i < 12)
	{
		test_multi.add(key_list[i], i);
		i++;
	}
	test_multi.create_graph();
	try
	{
		std::cout << test_multi[argv[1]] << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Not found" << std::endl;
	}
	return (0);
}