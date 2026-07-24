#include "Bot.hpp"
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <iostream>
#include <sstream>
#include <csignal>
#include "RPN.hpp"
#include <vector>
#define	BUFFER_SIZE 512

static volatile sig_atomic_t	sigIntQuit = 0;

static void	handleSig(int signum) {
	(void)signum;
	sigIntQuit = 1;
}

static void	setSignal() {
	struct sigaction sa;
	struct sigaction saSigPipe;	
	sa.sa_handler = handleSig;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	saSigPipe.sa_handler = SIG_IGN;
	sigemptyset(&saSigPipe.sa_mask);
	saSigPipe.sa_flags = 0;
	sigaction(SIGPIPE, &saSigPipe, NULL);
}

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

static std::string	jokes() {
	static const char	*jokesMsg[] = {
		"Comment mets t'on un éléphant dans un frigo ?",
		"On ouvre le frigo, on mets l'éléphant et on ferme le frigo.",
		"Quel est le meilleur point de vue démocratique ?",
		"Le string! Il sépare la gauche de la droite, protège le centre et unifie le regard du peuple. Mais attention, il ne faut pas trop tiré sur la ficelle, sinon en l'as dans le cul et on est dans la merde.",
		"Un aveugle rentre dans un bar, puis dans une table... puis dans une chaise....",
		"Tu veux une blague pédophile ? C'est un mec il rentre dans un bar...",
		"Comment mettre une giraffe dans un frigo ?",
		"On ouvre le frigo, on retire l'éléphant, on mets la giraffe et on ferme le frigo.",
		"Un peroquet dans un bar répète: \"Je veux du coca, je veux du coca\", le barman lui dis d'arrêter sinon il le cloue au mur. Le perroquet continue: \"Je veux du coca, je veux du coca\", le barman: \"Dernière fois\", \"Je veux du coc...\". Le perroguet se retrouve clouer au mur, il se retourne vers une statue de Jesus et demande \"Toi aussi tu voulais du coca ?\".",
		"Le lion fais une grande fête ou tout les animaux sont invité, mais il en manque un, lequel ?",
		"La giraffe! Elle est toujours dans le frigo!",
		"Un mec rentre dans un café... plouf!",
		"Il y a une rivière tout le temps infester de crocodile et tu dois la traversé, comment faire ?",
		"Y aller tranquillement, ils sont tous à la fête du Lion!"
	};
	static const size_t	jokesMsgSize = sizeof(jokesMsg) / sizeof(const char *);
	static size_t	i = 0;
	if (i >= jokesMsgSize)
		i = 0;
	return (jokesMsg[i++]);
}

bool	Bot::_register(int sockFd) {
	std::string	welcome = " 001 ";
	welcome.append(this->_name).append(" :Welcome");
	std::string	registerToServ = "PASS ";
	registerToServ.append(this->_password).append("\r\nNICK ").append(this->_name).append("\r\nUSER ").append(this->_name).append(" 0 * :bot").append(this->_name).append("\r\n").append("MODE ").append(this->_name).append(" +B").append("\r\n");
	int	sendValue;
	sendValue = send(sockFd, registerToServ.c_str(), registerToServ.size(), 0);
	if (sendValue <= 0)
		return (close(sockFd), false);
	char	buffer[BUFFER_SIZE + 1];
	int	readValue;
	while (!sigIntQuit) {
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

void	Bot::_joinChannel(int sockFd, std::string &token, std::istringstream &iss) {
	if (token != this->_name)
		return ;
	std::string	channelName;
	iss >> channelName;
	if (channelName.empty())
		return ;
	std::string	cmd("JOIN ");
	cmd.append(channelName).append("\r\n");
	std::cout << cmd << std::endl;
	send(sockFd, cmd.c_str(), cmd.size(), 0);
}

void	Bot::doCommand(std::string &cmdLine, int sockFd) {
	std::istringstream	iss(cmdLine);
	std::string	sendSrc;
	std::string	cmd;
	iss >> sendSrc >> cmd;
	if (iss.fail() || iss.eof() || (cmd != "PRIVMSG" && cmd != "INVITE"))
		return ;
	std::cout << cmd << std::endl;
	std::string	token;
	iss >> token;
	if (iss.fail() || iss.eof() || token.empty())
	return ;
	std::cout << token << std::endl;
	if (cmd == "INVITE")
		return (this->_joinChannel(sockFd, token, iss));
	if (token != this->_name)
		cmd.append(1, ' ').append(token);
	else
		cmd.append(1, ' ').append(sendSrc.begin() + 1, sendSrc.begin() + sendSrc.find('!'));
	std::cout << cmd << std::endl;
	iss >> token;
	if (iss.fail() || token.empty())
		return ;
	if (token[0] == ':')
		token.erase(0, 1);
	if (token.empty())
		return ;
	std::cout << token << std::endl;
	if (token == "$ping")
		cmd.append(" :Pong !\r\n");
	else if (token == "$joke")
		cmd.append(" :").append(jokes()).append("\r\n");
	else if (token == "$lightspeed")
		cmd.append(" :299'792'458 ms\r\n");
	else if (token == "$second")
		cmd.append(" :9'192'631'770 periodes de radiation, Cesium 133\r\n");
	else if (token == "$rpn") {
		std::string	expression;
		iss >> expression;
		if (expression.empty())
			cmd.append(" :Pas assez d'arguments pour rpn :(\r\n");
		else {
			RPN	rpn;
			std::string	expRest;
			std::getline(iss, expRest);
			size_t	ri = expRest.find('\r');
			if (ri != std::string::npos)
				expRest.erase(ri, expRest.size() - ri);
			cmd.append(" :").append(rpn.rpn(expression.append(expRest))).append("\r\n");
		}
	}
	else
		return ;
	std::cout << cmd << std::flush;
	send(sockFd, cmd.c_str(), cmd.size(), 0);
}

bool	Bot::run() {
	if (this->_port < 0)
		return (false);
	setSignal();
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
	while (!sigIntQuit) {
		readValue = recv(sockFd, buffer, BUFFER_SIZE, 0);
		if (readValue <= 0)
			return (close(sockFd), false);
		buffer[readValue] = '\0';
		this->_bufferIn += buffer;
		while (!sigIntQuit) {
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
