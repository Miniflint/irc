#include "Server.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <algorithm>
#include <csignal>
#ifdef __APPLE__
#elif defined(__linux__)
# include <sys/epoll.h>
# define MAX_EVENTS 10
#endif

static int	initListenSocket(int port) {
	int	listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSock == -1)
		return (-1);
	int	opt = 1;
	setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	fcntl(listenSock, F_SETFL, O_NONBLOCK);
	struct sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(listenSock, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr));
	listen(listenSock, SOMAXCONN);
	return (listenSock);
}

void Server::delClient(int fd) {
	close(fd);
	Client *c = this->_clients[fd];
	std::string nick = c->getNick();
	if (!nick.empty()) {
		std::list<Channel>::iterator end = this->_channel.end();
		for (std::list<Channel>::iterator it = this->_channel.begin(); it != end; it++) {
			try {
				c->getChannel()[it->getNick()];
				std::vector<size_t> &clientFd = it->getClientsFD();
				std::vector<size_t>::iterator rtn = std::find(clientFd.begin(), clientFd.end(), c->getFd());
				if (rtn != clientFd.end())
					clientFd.erase(rtn);
			} catch (std::exception &e) {(void)e;}
		}
		this->_clientTrie.del(nick);
	}
	if (c != NULL) {
		delete c;
		this->_clients[fd] = NULL;
	}
	std::cout << nick << ": Deconected" << std::endl;
}

int Server::newConnection()
{
	struct sockaddr_in	addr;
	socklen_t			addrLen = sizeof(addr);
	int	clientSock = accept(this->_sockServerFD, reinterpret_cast<struct sockaddr *>(&addr), &addrLen);
	if (clientSock == -1)
		return (-1);
	char* host = inet_ntoa(addr.sin_addr);
	int port = ntohs(addr.sin_port);
	fcntl(clientSock, F_SETFL, O_NONBLOCK);
	if (static_cast<size_t>(clientSock) >= this->_clients.size())
		this->_clients.resize(static_cast<size_t>(clientSock) + 1, NULL);
	if (!this->_clients[clientSock]) {
		this->_clients[clientSock] = new Client(clientSock, host, port);
	} else {
		return (-1);
	}
	std::cout << "New Client connected: IP: " << host << " port: " << port << std::endl;
	return (clientSock);
}

#ifdef __APPLE__
#elif defined(__linux__)

void	delEpollClient(Server &serv, int epfd, int fd) {
	struct epoll_event ev;
	std::memset(&ev, 0, sizeof(ev)); 
	epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
	serv.delClient(fd);
}

static void	setEpollMode(int epfd, int fd, uint16_t mode, uint32_t flag) {
	struct epoll_event ev;
	std::memset(&ev, 0, sizeof(ev));
	ev.events = flag;
	ev.data.fd = fd;
	epoll_ctl(epfd, mode, fd, &ev);
}

bool	Server::run() {
	signal(SIGPIPE, SIG_IGN);
	if ((this->_sockServerFD = initListenSocket(this->_port)) == -1)
		return (false);
	int epfd = epoll_create(1);
	if (epfd == -1) {
		close(this->_sockServerFD);
		return (false);
	}
	struct epoll_event ev;
	std::memset(&ev, 0, sizeof(ev));
	ev.events = EPOLLIN;
	ev.data.fd = this->_sockServerFD;
	epoll_ctl(epfd, EPOLL_CTL_ADD, this->_sockServerFD, &ev);
	struct epoll_event events[MAX_EVENTS];
	while (true) {
		int nEvents = epoll_wait(epfd, events, MAX_EVENTS, -1);
		for (int i = 0; i < nEvents; ++i) {
			if (events[i].data.fd == this->_sockServerFD) {
				int	newClientFd = this->newConnection();
				setEpollMode(epfd, newClientFd, EPOLL_CTL_ADD, EPOLLIN);
			} else if (events[i].events & (EPOLLHUP | EPOLLERR)) {
				delEpollClient(*this, epfd, events[i].data.fd);
			} else {
				if (events[i].events & EPOLLIN) {
					char	buffer[MAX_PACKET_SIZE + 1];
					ssize_t	readN = recv(events[i].data.fd, buffer, MAX_PACKET_SIZE, 0);
					if (readN < 1) {
						delEpollClient(*this, epfd, events[i].data.fd);
						continue ;
					}
					buffer[readN]= '\0';
					this->_clients[events[i].data.fd]->buffer += buffer;
					this->doCommand(events[i].data.fd);
					while (!this->poolOut.empty()) {
						int	outFd = this->poolOut.front();
						setEpollMode(epfd, outFd, EPOLL_CTL_MOD, EPOLLIN | EPOLLOUT);
						this->poolOut.pop();
					}
				}
				if (events[i].events & EPOLLOUT) {
					int	outFd = events[i].data.fd;
					size_t	buffSize = this->_clients[outFd]->getBufferOut().size() < MAX_PACKET_SIZE ? this->_clients[outFd]->getBufferOut().size() : MAX_PACKET_SIZE;
					ssize_t	writeN = send(outFd, this->_clients[outFd]->getBufferOut().c_str(), buffSize, 0);
					if (writeN != -1) {
						this->_clients[outFd]->getBufferOut().erase(0, writeN);
					} else {
						delEpollClient(*this, epfd, events[i].data.fd);
						continue;
					}
					if (this->_clients[outFd]->getBufferOut().empty())
						setEpollMode(epfd, outFd, EPOLL_CTL_MOD, EPOLLIN);
				}
			}
		}
		while (!this->poolQuit.empty()) {
			int	outFd = this->poolQuit.front();
			delEpollClient(*this, epfd, outFd);
			this->poolQuit.pop();
		}
	}
	close(epfd);
	close(this->_sockServerFD);
	return (true);
}
#endif

// static int	initListenSocket(int port) {
// 	//socket() crée un socket.
// 	// AF_INET pour lui préciser de domain comme local (AF_LOCAL), ipv4 (AF_INET), ipv6 (AF_INET6) etc...
// 	// SOCK_STREAM flag pour le protocol de communication, SOCK_STREAM pour TCP et SOCK_DGRAM pour UDP
// 	// Dernière value pour le protocol, 0 laisse l'os selectionner le protocol en utilisant le flag précédant comme SOCK_STREAM pour TCP
// 	int	listenSock = socket(AF_INET, SOCK_STREAM, 0);
// 	if (listenSock == -1)
// 		return (-1);
// 	//setsockopt() modifie les options d'un socket.
// 	//listenSock le socket que l'on va modifier
// 	//SOL_SOCKET le niveau de couche à modifier, chaque niveau à des parametre de modification différent, SOL_SOCKET permet de modifier le socket en lui même indépendament de sont protocol ou son type d'IP etc...
// 	//SO_REUSEADDR option pour autoriser une addresse directement à la fin du programme pour évité les erreur d'adresses déjà utiliser en cas de crash et de relance. Cette option s'applique au niveau du socket donc SOL_SOCKET.
// 	//opt pointeur sur int valant un pour dire "activer l'option", pour certine option, opt peut servir de valeur de set.
// 	int	opt = 1;
// 	setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
// 	//passer le socket en mode non bloquant pour la lecture et l'ecriture
// 	fcntl(listenSock, F_SETFL, O_NONBLOCK);
// 	//struct sockaddr_in addr, structure pour fournir le port et l'address ip du socket
// 	struct sockaddr_in addr;
// 	std::memset(&addr, 0, sizeof(addr));
// 	addr.sin_family = AF_INET;
// 	//htons converti dans la langue du réseau le port
//	 addr.sin_port = htons(port);
// 	//INADDR_ANY correspond à 0.0.0.0, comme ça on écoute sur toutes kes cartes réseau de la machine en même temps
//	 addr.sin_addr.s_addr = INADDR_ANY;
// 	//bond connect l'IP et le port au socket
// 	bind(listenSock, (struct sockaddr *)&addr, sizeof(addr));
// 	//listen passe le socket en mode écoute
// 	//set la taille max de la liste d'écoute, SOMAXCONN est une constat de l'OS pour le nombre max de nouvelles connexion qui n'ont pas encore été traitées par accept() dans la liste d'attente.
// 	listen(listenSock, SOMAXCONN);
// 	return (listenSock);
// }

// bool	Server::run() {
// 	if ((this->_sockServerFD = initListenSocket(this->_port)) == -1)
// 		return (false);
// 	//crée une instance d'epoll, la valeur n'est plus utiliser sur les systeme actuel (anciennement le nombre de fd prévu à écouter) mais doit être superieur à 1
// 	this->_epfd = epoll_create(1);
// 	if (this->_epfd == -1) {
// 		close(this->_sockServerFD);
// 		return (false);
// 	}
// 	//struct epoll_event ev, structure pour fournir le listen socket et passer epoll en mode EPOLLIN (révéiller uniquement si le socket reçoit qque chose)
// 	struct epoll_event ev;
//	 std::memset(&ev, 0, sizeof(ev));
//	 ev.events = EPOLLIN;
//	 ev.data.fd = this->_sockServerFD;
// 	//epoll_ctl permet de controler une instance d'epoll, EPOLL_CTL_ADD pour ajouter un event ou modifier un socket
//	 // Ajout du socket à epoll
//	 epoll_ctl(this->_epfd, EPOLL_CTL_ADD, this->_sockServerFD, &ev);
// 	//tableau de récupération des events
//	 struct epoll_event events[MAX_EVENTS];
// 	while (true) {
// 		//récupérer les events dans events, retourne le nombre d'events reçu, -1 timout infini, sinon mettre en milliseconde
// 		int nEvents = epoll_wait(this->_epfd, events, MAX_EVENTS, -1);
// 		for (int i = 0; i < nEvents; ++i) {

// 		}
// 	}
// 	close(this->_epfd);
// 	close(this->_sockServerFD);
// 	return (true);
// }
