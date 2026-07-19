## TOP PRIORITY
1. [x] Faire NICK
1. [x] Faire USER
1. [x] Faire boucle event
   - [x] recv()
   - [x] send()
1. [x] Faire Server::sendToClient()
1. [x] Faire PRIVMSG
2. [ ] Prendre en compte tout les modes pour PRIVMSG
3. [x] Faire channels
4. [X] Faire JOIN
   - [ ] si invité, bypass MDP
6. [x] faire LIST
5. [ ] faire KICK
6. [x] faire TOPIC //new à test
7. [ ] faire MODE
8. [ ] Faire INVITE //new à test
9. [ ] Faire README.MD
10. [x] Enlever fcntl de events.cpp

## PRIORITY

1. [X] ajouter code erreur
2. [ ] Faire QUIT // change messages
3. [ ] Faire KILL
4. [ ] Faire PART // verify message //faire liste de channel
5. [x] faire DIE
6. [x] faire RESTART
7. [x] fair SIGQUIT
8. [ ] Regarder error et warning de halloy
9. [ ] tester 
   - [ ] faire UNIT_TEST // pour checker toute les fonctions

## Lower Priority

1. [ ] Terminer WHO // prendre en compte user et pas que channel
2. [ ] Faire AWAY // ajouter std::string avec un message
3. [ ] Faire HELP
4. [ ] Faire NAMES //namesrpl est déjà codé

## OTHERS

1. [x] Faire un bot
   - [x] comprends un message particulier
   - [x] répond au message
   - [ ] peut faire des commandes dynamiquement
   - [ ] join sur invite
2. [ ] Faire DCC