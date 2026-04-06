/* Ex 8.4: Client envoie répertoire (tar) au serveur */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF 4096

int main(int argc, char *argv[])
{
    if (argc != 4) 
    {
        fprintf(stderr, "Usage: %s adresse port repertoire\n", argv[0]);
        return 1;
    }
    // créer archive tar 
    char cmd[512];
    sprintf(cmd, "tar zcf /tmp/rep.tgz -C %s .", argv[3]);
    system(cmd);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {.sin_family=AF_INET, .sin_port=htons(atoi(argv[2]))};
    inet_aton(argv[1], &addr.sin_addr);
    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) 
    {
        perror("connect"); return 1;
    }
    FILE *f = fopen("/tmp/rep.tgz", "rb");
    char buf[BUF]; int n;
    while ((n = fread(buf, 1, BUF, f)) > 0)
        write(sock, buf, n);
    fclose(f);
    close(sock);
    unlink("/tmp/rep.tgz");
    printf("Répertoire envoyé.\n");
    return 0;
}
