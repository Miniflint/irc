#include "Bot.hpp"
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <iostream>
#include <sstream>
#define	BUFFER_SIZE 512

Bot::Bot(std::string ip, std::string port, std::string password, std::string name) : _ip(ip), _password(password), _name(name), _bufferIn(""), _bufferOut("") {
	std::istringstream	iss(port);
	iss >> this->_port;
	if (iss.fail())
		this->_port = -1;
}

Bot::Bot(const Bot &copy) {
	(void)copy;
}

Bot::~Bot() {}

Bot		&Bot::operator=(const Bot &copy) {
	(void)copy;
	return (*this);
}

bool	Bot::_register(int sockFd) {
	std::string	welcome = " 001 ";
	welcome.append(this->_name).append(" :Welcome");
	std::string	registerToServ = "PASS ";
	registerToServ.append(this->_password).append("\r\nNICK ").append(this->_name).append("\r\nUSER ").append(this->_name).append(" 0 * :bot").append(this->_name).append("\r\n");
	int	sendValue;
	sendValue = send(sockFd, registerToServ.c_str(), registerToServ.size(), 0);
	if (sendValue <= 0)
		return (close(sockFd), false);
	char	buffer[BUFFER_SIZE + 1];
	int	readValue;
	while (true) {
		readValue = recv(sockFd, buffer, BUFFER_SIZE, 0);
		if (readValue <= 0)
			return (close(sockFd), false);
		buffer[readValue] = '\0';
		this->_bufferIn += buffer;
		size_t finded = this->_bufferIn.find("\r\n");
		if (finded != std::string::npos) {
			std::string	msg;
			msg.assign(this->_bufferIn.begin(), this->_bufferIn.begin() + finded);
			this->_bufferIn.erase(0, finded + 2);
			if (msg.find(welcome) != std::string::npos) {
				std::cout << "Connected !!!" << std::endl;
				return (true);
			}
			std::cerr << "Not connected :(" << std::endl;
			return (close(sockFd), false);
		}
	}
	return (close(sockFd), false);
}

void	Bot::doCommand(std::string &cmdLine, int sockFd) {
	std::istringstream	iss(cmdLine);
	std::string	sendSrc;
	std::string	privmsg;
	iss >> sendSrc >> privmsg;
	if (iss.fail() || iss.eof() || privmsg != "PRIVMSG")
		return ;
	std::cout << privmsg << std::endl;
	std::string	token;
	iss >> token;
	if (iss.fail() || iss.eof() || token.empty())
		return ;
	std::cout << token << std::endl;
	if (token != this->_name)
		privmsg.append(1, ' ').append(token);
	else
		privmsg.append(1, ' ').append(sendSrc.begin() + 1, sendSrc.begin() + sendSrc.find('!'));
	std::cout << privmsg << std::endl;
	iss >> token;
	if (iss.fail() || token.empty())
		return ;
	if (token[0] == ':')
		token.erase(0, 1);
	if (token.empty())
		return ;
	std::cout << token << std::endl;
	if (token == "#ping")
		privmsg.append(" :Pong !\r\n");
	else if (token == "#joke")
		privmsg.append(" :C'est l'histoire d'une put*... [joke canceled]\r\n");
	else if (token == "#lightspeed")
		privmsg.append(" :299'792'458 ms\r\n");
	else if (token == "#second")
		privmsg.append(" :9'192'631'770 periodes de radiation, Cesium 133\r\n");
	else
		return ;
	std::cout << privmsg << std::flush;
	send(sockFd, privmsg.c_str(), privmsg.size(), 0);
}

bool	Bot::run() {
	if (this->_port < 0)
		return (false);
	int	sockFd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockFd < 0)
		return (false);
	struct sockaddr_in	servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(this->_port);
	servAddr.sin_addr.s_addr = inet_addr(this->_ip.c_str());
	if (servAddr.sin_addr.s_addr == INADDR_NONE)
		return (close(sockFd), false);
	if (connect(sockFd, reinterpret_cast<struct sockaddr *>(&servAddr), sizeof(servAddr)) == -1)
		return (close(sockFd), false);
	if (!this->_register(sockFd))
		return (false);
	char	buffer[BUFFER_SIZE + 1];
	int		readValue;
	while (true) {
		readValue = recv(sockFd, buffer, BUFFER_SIZE, 0);
		if (readValue <= 0)
			return (close(sockFd), false);
		buffer[readValue] = '\0';
		this->_bufferIn += buffer;
		while (true) {
			size_t found = this->_bufferIn.find("\r\n");
			if (found != std::string::npos) {
				std::string	msg;
				msg.assign(this->_bufferIn.begin(), this->_bufferIn.begin() + found);
				this->_bufferIn.erase(0, found + 2);
				std::cout << msg << std::endl;
				doCommand(msg, sockFd);
			} else
				break ;
		}
	}
	close(sockFd);
	return (true);
}
