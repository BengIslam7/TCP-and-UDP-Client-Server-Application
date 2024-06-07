# TCP-and-UDP-Client-Server-Application

# Application Client Serveur avec TCP

## Description

Ce projet est une application client-serveur développée en C avec une interface graphique utilisant GTK. L'application permet aux utilisateurs de se connecter à un serveur, de s'authentifier, et d'exécuter diverses actions telles que :

1. Afficher la date et l'heure courantes.
2. Lister les fichiers dans un répertoire spécifié sur le serveur.
3. Afficher le contenu d'un fichier spécifié.
4. Afficher la durée de la session client.

## Fonctionnalités

### Côté Client

- **Authentification :** Le client doit s'authentifier avec un nom d'utilisateur et un mot de passe pour accéder aux fonctionnalités.
- **Interface Graphique :** Utilise GTK pour une interface graphique conviviale. Les fonctionnalités disponibles sont accessibles via des boutons.
- **Actions Disponibles :**
  - **Date et Heure :** Affiche la date et l'heure actuelles du serveur.
  - **Liste des Fichiers :** Affiche la liste des fichiers dans le répertoire courant du serveur.
  - **Contenu du Fichier :** Affiche le contenu d'un fichier spécifié par l'utilisateur.
  - **Durée de la Session :** Affiche la durée de la session client.

### Côté Serveur

- **Gestion des Clients :** Le serveur peut gérer plusieurs clients simultanément (jusqu'à une limite définie).
- **Actions Disponibles :**
  - **Date et Heure :** Envoie la date et l'heure actuelles au client.
  - **Liste des Fichiers :** Envoie la liste des fichiers dans le répertoire courant au client.
  - **Contenu du Fichier :** Envoie le contenu d'un fichier spécifié au client.
  - **Durée de la Session :** Envoie la durée de la session au client.

## Prérequis

- GTK 3.0
- Bibliothèques standard de C (stdio.h, stdlib.h, string.h, unistd.h, arpa/inet.h, time.h)
- Environnement POSIX pour la gestion des sockets

## Compilation et Exécution

1. **Compilation :**
   
   make part2

2. **Exécution :**

 **Exécution côté Serveur**

   ./serveurTCP
   
 **Exécution côté Client**
   
   ./clientTCPUI
   
## Utilisation

1. **Lancement du Serveur :** Exécutez le serveur en premier sur la machine hôte.
2. **Lancement du Client :** Exécutez le client et connectez-vous en utilisant les informations d'identification suivantes :

   - Nom d'utilisateur : unix
   - Mot de passe : unix
    
4. **Utilisation de l'Interface Graphique :** Utilisez les boutons pour effectuer les différentes actions disponibles.

# Application Client Serveur avec UDP

## Description

Ce projet consiste en une application client-serveur utilisant des sockets UDP pour envoyer et recevoir des nombres aléatoires. Le client envoie un nombre aléatoire au serveur, et le serveur répond en renvoyant ce même nombre, suivi de la génération et de l'envoi de plusieurs nombres aléatoires au client.

## Fonctionnalités

### Côté Serveur

- Attend les connexions sur un port spécifié.
- Reçoit un nombre du client.
- Envoie ce nombre de retour au client comme confirmation.
- Génère et envoie une séquence de nombres aléatoires au client, correspondant au nombre initial reçu.

### Côté Client

- Envoie un nombre aléatoire au serveur.
- Reçoit une confirmation du nombre total de nombres aléatoires à recevoir.
- Reçoit et affiche les nombres aléatoires envoyés par le serveur.

## Prérequis

- Environnement POSIX pour la gestion des sockets (Linux, macOS, etc.)
- Compilateur C (GCC, Clang, etc.)

## Compilation et Exécution

1. **Compilation :**
   
   make 

2. **Exécution :**

**Exécution côté Serveur**

   ./server port
   
**Exécution côté Client**
   
   ./client address port

## Exemple d'Utilisation

### Exécution du Serveur

./server 8080

Sortie attendue :

Serveur en attente sur le port 8080...
Serveur : Nombre reçu du client : X
Serveur : X nombres aléatoires envoyés au client.

### Exécution du Client

./client 127.0.0.1 8080

Sortie attendue :

Client : Nombre aléatoire envoyé au serveur : X
Client : Nombre total de nombres aléatoires à recevoir : X
Client : Nombres aléatoires reçus du serveur : Y1 Y2 Y3 ... YX

## Détails de l'Implémentation

### Serveur

- Crée un socket UDP.
- Lie le socket à une adresse et un port.
- Attend de recevoir un nombre du client.
- Envoie le même nombre en guise de confirmation.
- Génère et envoie des nombres aléatoires au client.
- Ferme le socket à la fin de la communication.

### Client

- Crée un socket UDP.
- Génère un nombre aléatoire.
- Envoie ce nombre au serveur.
- Reçoit la confirmation du nombre total de nombres aléatoires à recevoir.
- Reçoit et affiche les nombres aléatoires envoyés par le serveur.
- Ferme le socket à la fin de la communication.

