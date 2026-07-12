#include "Server.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#ifdef __APPLE__
#elif defined(__linux__)
# include <sys/epoll.h>
# define MAX_EVENTS 10
#endif
#define BUFFER_SIZE 512

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

int Server::newConnection()
{
	struct sockaddr	addr;
	socklen_t		addrLen;
	int	clientSock = accept(this->_sockServerFD, &addr, &addrLen);
	if (clientSock == -1)
		return (-1);
	fcntl(clientSock, F_SETFL, O_NONBLOCK);
	if (static_cast<size_t>(clientSock) >= this->_clients.size())
		this->_clients.resize(static_cast<size_t>(clientSock) + 1, NULL);
	if (!this->_clients[clientSock]) {
		this->_clients[clientSock] = new Client(clientSock, addr, addrLen);
	} else {
		return (-1);
	}
	return (clientSock);
}

#ifdef __APPLE__
#elif defined(__linux__)
bool	Server::run() {
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
				int	newClientFD = this->newConnection();
				struct epoll_event evClient;
				std::memset(&ev, 0, sizeof(evClient));
				ev.events = EPOLLIN;
				ev.data.fd = newClientFD;
				epoll_ctl(epfd, EPOLL_CTL_ADD, newClientFD, &evClient);
			} else {
				char	buffer[BUFFER_SIZE];
				size_t	readN = recv(events[i].data.fd, buffer, BUFFER_SIZE + 1, 0);
				if (readN == -1)
					continue ;
				buffer[readN]= '\0';
				this->_clients[events[i].data.fd]->buffer += buffer;
				this->doCommand(events[i].data.fd);
			}
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
