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

+---------------------------------------------+
| 1. Création de l'instance epoll             |
|    int epfd = epoll_create1(0);             |
+---------------------------------------------+
                         |
                         v
+---------------------------------------------+
| 2. Ajout du socket serveur à epoll          |
|    server_event.events = EPOLLIN            |
|    server_event.data.fd = server_socket     |
|    epoll_ctl(epfd, EPOLL_CTL_ADD,           |
|              server_socket, &server_event); |
+---------------------------------------------+
                         |
                         v
+---------------------------------------------+
| 3. Déclaration du tableau d'événements      |
|    struct epoll_event events[MAX_EVENTS];   |
+---------------------------------------------+
                         |
                         v
+---------------------------------------------+
| 4. BOUCLE PRINCIPALE                        |
|    while (1) {                              |
|                                             |
|    +-------------------------------------+  |
|    | 4.1. Appel à epoll_wait             |  |
|    |                                     |  |
|    | int nfds = epoll_wait(epfd,         |  |
|    |                      events,        |  |
|    |                      MAX_EVENTS,    |  |
|    |                      -1);           |  |
|    +-------------------------------------+  |
|                     |                       |
|                     v                       |
|    +-------------------------------------+  |
|    | 4.2. BOUCLE DE TRAITEMENT           |  |
|    | for (int i = 0; i < nfds; i++) {    |  |
|    |                                     |  |
|    | +---------------------------------+ |  |
|    | | 4.2.1. Nouvelle connexion ?     | |  |
|    | | if (fd == server_socket) {      | |  |
|    | |     accept(...);                | |  |
|    | |     Ajouter client à epoll;     | |  |
|    | | }                               | |  |
|    | +---------------------------------+ |  |
|    |                                     |  |
|    | +---------------------------------+ |  |
|    | | 4.2.2. Données à lire ?         | |  |
|    | | if (events[i].events & EPOLLIN) | |  |
|    | | {                               | |  |
|    | |     recv(...);                  | |  |
|    | |     Traiter les données;        | |  |
|    | | }                               | |  |
|    | +---------------------------------+ |  |
|    |                                     |  |
|    | +---------------------------------+ |  |
|    | | 4.2.3. Prêt à écrire ?          | |  |
|    | | if (events[i].events            | |  |
|    | |     & EPOLLOUT) {               | |  |
|    | |     send(...);                  | |  |
|    | | }                               | |  |
|    | +---------------------------------+ |  |
|    |                                     |  |
|    | +---------------------------------+ |  |
|    | | 4.2.4. Erreur/Fermeture ?       | |  |
|    | | if (events[i].events &          | |  |
|    | |     (EPOLLHUP | EPOLLERR)) {    | |  |
|    | |     close(fd);                  | |  |
|    | |     epoll_ctl(..., DEL, ...);   | |  |
|    | | }                               | |  |
|    | +---------------------------------+ |  |
|    | }                                   |  |
|    +-------------------------------------+  |
| }                                           |
+---------------------------------------------+
