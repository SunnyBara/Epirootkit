#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 4444 

int main() {
    int server_fd, client_fd;          // descipteurs de sockets serveur et client
    char buffer[1024];                 // buffer pour stocker les données reçues
    struct sockaddr_in addr;           // structure pour l'adresse du serveur/client
    socklen_t addrlen = sizeof(addr);  

    // socket TCP IPv4
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Configuration de l'adresse du serveur
    addr.sin_family = AF_INET;          //  IPv4
    addr.sin_addr.s_addr = INADDR_ANY; // accepte les connexions sur toutes les interfaces réseau
    addr.sin_port = htons(PORT);        

    // on associe la socket à l'adresse et au port spécifiés
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);

    // on accepte la connexion entrante, création d'une nouvelle socket client
    client_fd = accept(server_fd, (struct sockaddr*)&addr, &addrlen);
    FILE *f = fopen("received_file", "wb");

    int n;
    // on lis les données reçues depuis la socket client, puis on écris dans le fichier
    while ((n = read(client_fd, buffer, 1024)) > 0) {
        fwrite(buffer, 1, n, f);
    }

    fclose(f);
    close(client_fd);
    close(server_fd);

    return 0;
}
