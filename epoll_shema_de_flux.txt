IRC : gestion des clients avec epoll : shema de flux
	

fcntl --> permet controler les propriete d'un fd

+---------------------------------------------+
| 1. Création de l'instance epoll             |
|    int epfd = epoll_create1(0);             | epfd : epoll file descriptor : reference pour l'instance epoll : struct eventpoll : struct rb_root rbr (arbre des fd surveilles), struct list_head rdllist (liste chaine des evenement pret), ...
+---------------------------------------------+
                         |
                         v
+---------------------------------------------+
| 2. Ajout du socket serveur à epoll          |
|    struct epoll_event sever_event           | struct epoll_event {uint32_t events; epoll_data_t data;};
|    server_event.events = EPOLLIN            | events : masque des evenements a surveiller : EPOLLIN (donnee dispo pour lecture), EPOLLOUT (pret pour send()), EPOLLERR (erreur sur le fd), EPOLLHUP (connexion fermee par le client)
|    server_event.data.fd = server_socket     | typedef union epoll_data {void *ptr; int fd; uint32_t u32; uint64_t u64;}; : *ptr (pointeur que l'on peut utiliser pour associer a un objet client par exemple, fd (fd du socket)
|    epoll_ctl(epfd, EPOLL_CTL_ADD,           | int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
|              server_socket, &server_event); |
+---------------------------------------------+
                         |
                         v
+---------------------------------------------+
| 3. Déclaration du tableau d'événements      |
|    struct epoll_event events[MAX_EVENTS];   | Tableau pour recevoir les événements prêts (ex: EPOLLIN, EPOLLOUT) retournés par epoll_wait(), server_event n'est plus utilise
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
|    | int nfds = epoll_wait(epfd,         |  | int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
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
|    | | if (events[i].events & EPOLLIN) | |  | comparaison binaire pour detecte la presence du masque EPOLLIN
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
