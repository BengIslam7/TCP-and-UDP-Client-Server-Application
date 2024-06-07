#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define NMAX 100

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <server_port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const int serverPort = atoi(argv[1]);

    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;

    // Création du socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        error("Erreur lors de la création du socket");
    }

    // Configuration de l'adresse du serveur
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(serverPort);

    // Liaison du socket avec l'adresse du serveur
    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        error("Erreur lors de la liaison du socket");
    }

    printf("Serveur en attente sur le port %d...\n", serverPort);

    int clientRequest;
    socklen_t addrLen = sizeof(clientAddr);

    // Réception du nombre du client
    recvfrom(sockfd, &clientRequest, sizeof(clientRequest), 0, (struct sockaddr*)&clientAddr, &addrLen);

    printf("Serveur : Nombre reçu du client : %d\n", clientRequest);

    // Envoi du nombre total de nombres aléatoires au client
    sendto(sockfd, &clientRequest, sizeof(clientRequest), 0, (struct sockaddr*)&clientAddr, addrLen);

    // Envoi des nombres aléatoires au client
    for (int i = 0; i < clientRequest; ++i) {
        int randomNumber = rand() % NMAX + 1;
        sendto(sockfd, &randomNumber, sizeof(randomNumber), 0, (struct sockaddr*)&clientAddr, addrLen);
    }

    printf("Serveur : %d nombres aléatoires envoyés au client.\n", clientRequest);

    close(sockfd);

    return 0;
}
