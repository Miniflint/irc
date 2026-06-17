#include "main.hpp"

# include <stdlib.h>
# include <ostream>

// int	key_print(std::string word)
// {
// 	std::ostream << word;
// }

# include <iostream>
# include <string>

int	main(int ac, char **argv)
{
	if (ac != 2)
		return (1);
	//std::string	key_list[] = {"ara", "arriver", "arrivage", "arriv", "arrimer", "ara", "apple", "application", "applic", "fete",
	//	"fetard", "fee", "coupe", "coup","coupable", "culpabilite"};
	std::string	key_list[] = {"app", "apple", "appl1"};
	(void)argv;
	Trie<int>	test_multi;
	//test_multi.add("raq", 0);
	//test_multi.add("ratisser", 2);
	//test_multi.add("ratackckckck", 2);
	//test_multi.create_graph();
	for (unsigned int i = 0; i < 15; i++)
	{
		test_multi.add2(key_list[i], i);
		try
		{
			//std::cout << test_multi[key_list[i]] << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << "Not found" << std::endl;
		}
	}
	try
	{
		std::cout << test_multi[argv[1]] << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Not found" << std::endl;
	}

	//std::ifstream test("t.txt");
	//std::string		buff;
	//int	i;
//
	//i = 0;
	//std::getline(test, buff);
	//while (!buff.empty())
	//{
	//	std::getline(test, buff);
	//	test_multi.add(buff, i++);
	//}
	test_multi.create_graph();
	return (0);
}
