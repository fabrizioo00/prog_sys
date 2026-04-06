/* Ex 8.2: Serveur TCP vérifie IP autorisée dans fichier + bienvenue par nom */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#define BUF 256

int verifier_ip(const char *ip, char *nom_out)
{
    FILE *f = fopen("add_autoris.txt", "r");
    if (!f) return 0;
    char lip[50], lnom[50];
    while (fscanf(f, "%s %s", lip, lnom) >= 1) 
    {
        if (strcmp(lip, ip) == 0) 
        {
            if (nom_out) strcpy(nom_out, lnom);
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void traite_client(int sock, struct sockaddr_in *client)
{
    char buf[BUF], nom[50] = "inconnu";
    char *ip = inet_ntoa(client->sin_addr);

    if (!verifier_ip(ip, nom)) 
    {
        sprintf(buf, "Accès refusé pour %s\n", ip);
        write(sock, buf, strlen(buf));
        close(sock);
        return;
    }
    sprintf(buf, "Bienvenue %s (%s) !\n", nom, ip);
    write(sock, buf, strlen(buf));
    /* echo */
    int n;
    while ((n = read(sock, buf, BUF)) > 0)
        write(sock, buf, n);
    close(sock);
}

int main(void)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1; setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in addr = {.sin_family=AF_INET, .sin_port=htons(33017),
                               .sin_addr.s_addr=htonl(INADDR_ANY)};
    bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    listen(sock, 5);
    printf("Serveur en écoute port 33017\n");

    while (1) 
    {
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int csock = accept(sock, (struct sockaddr*)&client, &len);
        if (csock < 0) continue;
        pid_t pid = fork();
        if (pid == 0) 
        { 
            close(sock); 
            traite_client(csock, &client); 
            exit(0); 
        }
        close(csock);
        waitpid(-1, NULL, WNOHANG);
    }
    return 0;
}
