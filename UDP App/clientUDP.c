#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define NMAX 5

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_address> <server_port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *serverAddress = argv[1];
    const int serverPort = atoi(argv[2]);

    int sockfd;
    struct sockaddr_in serverAddr;

    // Création du socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        error("Erreur lors de la création du socket");
    }

    // Configuration de l'adresse du serveur
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    if (inet_pton(AF_INET, serverAddress, &serverAddr.sin_addr) <= 0) {
        error("Erreur lors de la conversion de l'adresse");
    }

    // Génération d'un nombre aléatoire entre 1 et NMAX
    srand(time(NULL));
    int randomNumber = rand() % NMAX + 1;

    // Envoi du nombre au serveur
    sendto(sockfd, &randomNumber, sizeof(randomNumber), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    printf("Client : Nombre aléatoire envoyé au serveur : %d\n", randomNumber);

    // Attente du nombre total de nombres aléatoires du serveur
    int totalNumbers;
    socklen_t addrLen = sizeof(serverAddr);
    recvfrom(sockfd, &totalNumbers, sizeof(totalNumbers), 0, (struct sockaddr*)&serverAddr, &addrLen);

    printf("Client : Nombre total de nombres aléatoires à recevoir : %d\n", totalNumbers);

    // Réception et affichage des nombres aléatoires du serveur
    printf("Client : Nombres aléatoires reçus du serveur : ");
    for (int i = 0; i < totalNumbers; ++i) {
        int receivedNumber;
        recvfrom(sockfd, &receivedNumber, sizeof(receivedNumber), 0, (struct sockaddr*)&serverAddr, &addrLen);
        printf("%d ", receivedNumber);
    }
    printf("\n");

    close(sockfd);

    return 0;
}