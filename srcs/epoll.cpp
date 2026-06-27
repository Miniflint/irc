#include <sys/epoll.h>
#include <fcntl.h>

#define MAX_EVENT	10
#define BUFFER_SIZE 512

int	main {
	
	//soket stuff

	int flags = fcntl(serveur_socket, F_GETFL, 0);

	//sokcket stuff : configuration de l'addresse du serveur

	//socket stuff : liaison du socket a l'addresse

	//socket stuff : mise en ecoute du socket

/////////// creation de l'instance epoll
	int epfd = epoll_create1(0);
	if (epoll_fd == -1) {
		// throw une erreur ou juste la print // "epoll_create1() failed"
		exit(EXIT_FAILURE);
	}

/////////// ajout du socket server a l'instance epoll
	struct epoll_event	server_event;
	server_event.events = EPOLLIN;
	server_event.data.fd = server_socket;
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, server_socket, &server_event) == -1) {
		// throw une erreur ou la print // "epoll_ctl failed for serveur
		exit(EXIT_FAILURE);
	}

	struct epoll_event	events[MAX_EVENT];
	char				Buffer[BUFFER_SIZE];

	while (1) {
		int nfds = epoll_wait(epoll_fd, events, MAX_EVENT, -1);
		if (nfds == -1)
