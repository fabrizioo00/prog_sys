/* Ex 8.3: Client envoie fichier texte au serveur (chemin en argument) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF 1024

int main(int argc, char *argv[])
{
    if (argc != 4) 
    {
        fprintf(stderr, "Usage: %s adresse port fichier\n", argv[0]);
        return 1;
    }
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {.sin_family=AF_INET, .sin_port=htons(atoi(argv[2]))};
    inet_aton(argv[1], &addr.sin_addr);
    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) 
    {
        perror("connect"); return 1;
    }
    //0 envoie le contenu du fichier 
    FILE *f = fopen(argv[3], "r");
    if (!f) 
    { 
        perror("fopen"); 
        close(sock); 
        return 1; 
    }
    char buf[BUF];
    int n;
    while ((n = fread(buf, 1, BUF, f)) > 0)
        write(sock, buf, n);
    fclose(f);
    close(sock);
    printf("Fichier envoyé.\n");
    return 0;
}
