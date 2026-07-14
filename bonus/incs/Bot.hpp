#ifndef BOT_HPP
# define BOT_HPP

# include <string>

class Bot {
	public:
		Bot(std::string ip, std::string port, std::string password, std::string name);
		Bot(const Bot &copy);
		~Bot();
		Bot		&operator=(const Bot &copy);
		bool	run();
		void	doCommand(std::string &cmdLine, int sockFd);
	private:
		Bot();
		bool	_register(int sockFd);
		std::string _ip;
		int			_port;
		std::string	_password;
		std::string _name;
		std::string	_bufferIn;
		std::string	_bufferOut;
};

#endif
