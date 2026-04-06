/* Ex 8.5: Serveur messagerie - met 2 clients en relation de façon concurrente */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h> 

#define BUF 256

//  pour gérer la conversation d'une paire isolée 
void gere_conversation(int s1, int s2) 
{
    write(s1, "Partenaire connecté ! Vous commencez.\nSaisissez: ", 50);
    write(s2, "Partenaire connecté ! En attente de son message...\n", 52);

    char buf[BUF];
    int n, current_writer = 1; // 1=s1 écrit, 2=s2 écrit 
    
    while (1) 
    {
        int wsock = (current_writer == 1) ? s1 : s2;
        int rsock = (current_writer == 1) ? s2 : s1;
        
        n = read(wsock, buf, BUF - 1); // On garde un octet pour le '\0' de sécurité
        if (n <= 0) break;
        
        buf[n] = '\0';
        buf[strcspn(buf, "\r\n")] = 0;
        
        char msg[BUF + 50];
        sprintf(msg, "L'autre client dit : %s\nSaisissez la réponse : ", buf);
        write(rsock, msg, strlen(msg));
        
        current_writer = (current_writer == 1) ? 2 : 1;
    }
    
    close(s1); 
    close(s2);
}

int main(void)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1; setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in addr = {.sin_family=AF_INET, .sin_port=htons(33020),
                               .sin_addr.s_addr=htonl(INADDR_ANY)};
    bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    listen(sock, 5);
    printf("Serveur messagerie port 33020 (Multipaires)\n");

    while (1) 
    {
        struct sockaddr_in c1, c2;
        socklen_t len = sizeof(c1);
        
        printf("En attente du premier client de la paire...\n");
        int s1 = accept(sock, (struct sockaddr*)&c1, &len);
        if (s1 < 0) continue;
        write(s1, "En attente d'un partenaire...\n", 30);
        
        printf("En attente du deuxième client de la paire...\n");
        len = sizeof(c2);
        int s2 = accept(sock, (struct sockaddr*)&c2, &len);
        if (s2 < 0) 
        {
            close(s1); // Si le 2ème fail, on éjecte le 1er pour éviter un déséquilibre
            continue;
        }

        printf("Paire formée ! Délégation à un processus fils.\n");
        
        pid_t pid = fork();
        if (pid == 0) 
        { 
             
            close(sock); // Le fils ne gère pas les nouvelles connexions
            gere_conversation(s1, s2);
            exit(0); 
        }
        
         
        close(s1); // Le père n'a plus besoin des sockets de ces clients
        close(s2);
        
        // Nettoyage "à la volée" des fils terminés
        waitpid(-1, NULL, WNOHANG);
    }

    return 0;
}