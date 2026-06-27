IRC : gestion des clients avec epoll : shema de flux

			________________
			|epoll_create(1)| -------> return : epfd (epoll fd) : int : !!!!!!close(epfd)!!!!!!!
			|_______________| -------> param : nombre de fd (socket) a surveiller : ignore car maintenant le kernel gere de facon dynamique
					|		  -------> descr. : cree une instance epoll
					|
		________________________
		|while(1)
		|

fcntl --> permet controler les propriete d'un fd
