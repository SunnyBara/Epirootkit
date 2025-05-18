#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 4444 

int main(int argc, char *argv[]) {
    // verif du nombre d'arguments (IP + nom de fichier)
    if (argc != 3) {
        printf("Usage: %s <IP> <filename>\n", argv[0]);
        return 1;
    }

    // socket tcp
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // config addresse serveur
    struct sockaddr_in server;
    server.sin_family = AF_INET;          // adresses IPv4
    server.sin_port = htons(PORT);        // port converti en format réseau
    inet_pton(AF_INET, argv[1], &server.sin_addr); // conversion ip en binaire

    // essayer de se connecter au serveur 
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Connection failed"); 
        return 1;
    }

    // ouvre le fichier en mode binaire 
    FILE *f = fopen(argv[2], "rb");

    char buffer[1024];
    int n;

    // lecture du fichier par blocs de 1024 octets et envoi au serveur
    while ((n = fread(buffer, 1, 1024, f)) > 0) {
        send(sock, buffer, n, 0);  // envoyer les données lues
    }

    fclose(f);
    close(sock);

    return 0;
}
