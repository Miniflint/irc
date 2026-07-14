#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "Bot.hpp"
# define BOT_NAME "Kevin"

int main(int ac, char **av)
{
	if (ac < 4) {
		std::cout << av[0] << " <server_ip> <server_port> <server_password> optional<bot_name>" << std::endl;
		return (1);
	}
    std::string name;
    if (ac > 4)
        name = av[4];
    else
        name = BOT_NAME;
    Bot bot(av[1], av[2], av[3], name);
    return bot.run();
}
