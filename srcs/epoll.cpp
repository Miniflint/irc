#include <sys/epoll.h>
#include <fcntl.h>

int	main {
	
	//soket stuff

	int flags = fcntl(serveur_socket, F_GETFL, 0);

	//sokcket stuff : configuration de l'addresse du serveur

	//socket stuff : liaison du socket a l'addresse

	//socket stuff : mise en ecoute du socket

	int epfd = epoll_create1(0);
	if (epoll_fd == -1) {
		// throw une erreur ou juste la print // "epoll_create1() failed"
		exit (EXIT_FAILURE);
	}
