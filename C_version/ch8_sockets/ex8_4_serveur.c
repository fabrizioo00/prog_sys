/* Ex 8.4: Serveur reçoit archive tar et l'extrait dans /home/save/ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#define BUF 4096

void traite_client(int sock, struct sockaddr_in *client)
{
    char *ip = inet_ntoa(client->sin_addr);
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char dir[256];
    
    // Utilisation de /home/save/ 
    sprintf(dir, "/home/save/%s_%04d%02d%02d", ip,
            tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday);
    
    // On crée le répertoire (en supposant que /home/save existe déjà) 
    mkdir(dir, 0755);

    
    char tmpf[] = "/tmp/recv_XXXXXX.tgz";
    int fd = mkstemp(tmpf);
    if (fd < 0) 
    {
        perror("mkstemp");
        close(sock);
        return;
    }

    char buf[BUF]; int n;
    while ((n = read(sock, buf, BUF)) > 0)
        write(fd, buf, n);
    close(fd);
    close(sock);

    char cmd[512];
    
    sprintf(cmd, "cd %s && tar zxf %s && rm %s", dir, tmpf, tmpf);
    system(cmd);
    printf("Répertoire extrait dans %s\n", dir);
}

int main(void)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1; setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in addr = {.sin_family=AF_INET, .sin_port=htons(33019),
                               .sin_addr.s_addr=htonl(INADDR_ANY)};
    bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    listen(sock, 5);
    
    printf("Serveur backup en écoute port 33019\n");
    
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