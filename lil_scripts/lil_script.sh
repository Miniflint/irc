#!/bin/bash

# Configuration du serveur
SERVER="127.0.0.1"
PORT="6667"
PASSWORD="pass"
NICKNAME="mini2"
USERNAME="miniflin2"
REALNAME="anyUser3"

echo "=== Connexion automatique à $SERVER:$PORT ==="

# Ouverture d'un descripteur de fichier bidirectionnel (3) sur le socket TCP
exec 3<>/dev/tcp/$SERVER/$PORT

writeServer()
{
    echo -en "$1\r\n" >&3
}

# 1. Envoi immédiat des commandes d'initialisation (sans ':' pour le REQ comme Halloy)
writeServer "CAP LS 302"
writeServer "PASS $PASSWORD"
writeServer "NICK $NICKNAME"
writeServer "USER $USERNAME 0 * :$REALNAME"

# Boucle de lecture en arrière-plan pour gérer les réponses du serveur
while read -r line <&3; do
    # Nettoyer les caractères de retour chariot (\r) pour éviter les bugs de parsing
    line=$(echo "$line" | tr -d '\r')
    
    # Affichage en temps réel des messages reçus du serveur
    echo "[SERVEUR] -> $line"

    # CAS A : Le serveur envoie sa liste CAP LS
    if [[ "$line" == *"CAP * LS"* ]]; then
        echo "[CLIENT]  -> Demande de capacité (echo-message)..."
        # On imite Halloy : pas de ':' devant echo-message si c'est le seul argument
        writeServer "CAP REQ echo-message"
    fi
    
    # CAS B : Le serveur valide la capacité (ACK)
    if [[ "$line" == *"CAP * ACK"* ]]; then
        echo "[CLIENT]  -> Validation reçue. Clôture de la négociation (CAP END)..."
        writeServer "CAP END"
    fi
    
    # CAS C : Le serveur envoie un PING de contrôle de présence
    if [[ "$line" =~ ^PING[[:space:]](.+) ]]; then
        TOKEN="${BASH_REMATCH[1]}"
        echo "[CLIENT]  -> Réponse au PING (PONG $TOKEN)..."
        writeServer "PONG $TOKEN"
    fi
    
    # CAS D : Message de bienvenue 001 reçu (Enregistrement validé avec succès)
    if [[ "$line" == *" 001 "* ]]; then
        echo "=== [SUCCÈS] Connexion établie et enregistrée ! ==="
        echo "=== Vous pouvez maintenant taper vos messages ci-dessous. ==="
    fi
done &

TOTAL_CHANNELS=1000000
COUNTER=1

sleep 3
while [ $COUNTER -le $TOTAL_CHANNELS ]; do
    # Création du nom du canal (ex: #channel1, #channel2)
    CHANNEL_NAME="#channel_$COUNTER"
    
    echo "[CLIENT] -> Création/Navigation vers le canal: $CHANNEL_NAME"
    
    # Envoi de la commande JOIN via votre fonction writeServer
    writeServer "JOIN $CHANNEL_NAME"
    
    # Incrémentation du compteur
    COUNTER=$((COUNTER + 1))

done

# Sauvegarde du PID de la boucle de lecture pour pouvoir la fermer à la fin
BG_PID=$!

# 2. Boucle principale : Envoi manuel de commandes/messages depuis le terminal
while read -r user_input; do
    # Si l'utilisateur tape QUIT, on ferme proprement
    writeServer "$user_input"
    if [[ "$user_input" == "QUIT" ]]; then
        echo "QUIT :Déconnexion demandée par l'utilisateur" >&3
        break
    fi
done

# Nettoyage des processus et fermeture du socket à la sortie
kill $BG_PID 2>/dev/null
exec 3>&-
echo "=== Connexion fermée ==="