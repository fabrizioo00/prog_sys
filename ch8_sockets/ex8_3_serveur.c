/* Ex 8.3: Serveur reçoit fichier et le sauvegarde avec IP+date dans /home/save/ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <time.h>

#define BUF 1024

void traite_client(int sock, struct sockaddr_in *client)
{
    char *ip = inet_ntoa(client->sin_addr);
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char fname[256];
    

    sprintf(fname, "/home/save/fichier_%s_%04d_%02d_%02d.txt", ip,
            tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday);

    FILE *f = fopen(fname, "w");
    if (!f) 
    { 
        perror("Erreur fopen"); 
        close(sock); 
        return; 
    }
    
    char buf[BUF]; 
    int n;
    while ((n = read(sock, buf, BUF)) > 0)
        fwrite(buf, 1, n, f);
        
    fclose(f);
    printf("Fichier sauvé: %s\n", fname);
    close(sock);
}

int main(void)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1; 
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in addr = {.sin_family=AF_INET, .sin_port=htons(33018),
                               .sin_addr.s_addr=htonl(INADDR_ANY)};
    bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    listen(sock, 5);
    
    printf("Serveur sauvegarde en écoute port 33018\n");
    
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