/* Ex 8.6: Forum de chat multi-thread
 * Les clients tapent 1 pour demander la parole. Un seul parle à la fois.
 * Le serveur diffuse le message + IP à tous les autres clients.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>

#define BUF 256
#define MAX_CLIENTS 50

int clients[MAX_CLIENTS];
char client_ips[MAX_CLIENTS][20];
// Initialisation explicite des sockets à -1 pour indiquer qu'elles sont libres 

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t parole = PTHREAD_MUTEX_INITIALIZER;

void broadcast(int sender, const char *msg)
{
    pthread_mutex_lock(&mtx);
    for (int i = 0; i < MAX_CLIENTS; i++) 
    {
        if (clients[i] != sender && clients[i] > 0) 
        {
            write(clients[i], msg, strlen(msg));
        }
    }
    pthread_mutex_unlock(&mtx);
}

void *handle_client(void *arg)
{
    int idx = (long)arg;
    int sock = clients[idx];
    char buf[BUF], msg[BUF + 100];

    sprintf(msg, "Bienvenue ! Tapez 1 pour demander la parole.\n");
    // Le cours indique de protéger l'accès en écriture aux sockets 
    pthread_mutex_lock(&mtx);
    write(sock, msg, strlen(msg));
    pthread_mutex_unlock(&mtx);

    while (1) 
    {
        int n = read(sock, buf, BUF - 1);
        if (n <= 0) break; // Déconnexion ou erreur
        
        buf[n] = '\0'; // Sécurisation de la chaîne
        buf[strcspn(buf, "\r\n")] = 0;
        
        if (strcmp(buf, "1") == 0) 
        {
            // Verrouillage du droit de parole
            pthread_mutex_lock(&parole);
            
            pthread_mutex_lock(&mtx);
            write(sock, "Vous avez la parole, envoyez votre message:\n", 44);
            pthread_mutex_unlock(&mtx);
            
            n = read(sock, buf, BUF - 1);
            if (n <= 0) 
            {
                // Si le client se déconnecte pendant qu'il a la parole, on libère le jeton !
                pthread_mutex_unlock(&parole);
                break;
            }
            
            buf[n] = '\0';
            buf[strcspn(buf, "\r\n")] = 0;
            
            sprintf(msg, "[%s] : %s\n", client_ips[idx], buf);
            broadcast(sock, msg);
            
            pthread_mutex_lock(&mtx);
            write(sock, "Message envoyé. Tapez 1 pour reparler.\n", 39);
            pthread_mutex_unlock(&mtx);
            
            // Libération du droit de parole pour les autres
            pthread_mutex_unlock(&parole);
        }
    }
    
    // Nettoyage à la déconnexion 
    pthread_mutex_lock(&mtx);
    printf("Déconnexion du client [%d] %s\n", idx, client_ips[idx]);
    clients[idx] = -1; // Libère l'emplacement
    pthread_mutex_unlock(&mtx);
    
    close(sock);
    return NULL;
}

int main(void)
{
    // Initialisation du tableau de clients à -1 (vide) 
    for(int i = 0; i < MAX_CLIENTS; i++) 
    {
        clients[i] = -1;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1; setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in addr = {.sin_family=AF_INET, .sin_port=htons(33021),
                               .sin_addr.s_addr=htonl(INADDR_ANY)};
    bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    listen(sock, 5);
    printf("Forum chat port 33021 (Multi-Thread avec file d'attente de parole)\n");

    while (1) 
    {
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int csock = accept(sock, (struct sockaddr*)&client, &len);
        if (csock < 0) continue;

        pthread_mutex_lock(&mtx);
        
        // Recherche d'un emplacement libre
        int idx = -1;
        for(int i = 0; i < MAX_CLIENTS; i++) 
        {
            if(clients[i] == -1) 
            {
                idx = i;
                break;
            }
        }
        
        if (idx == -1) 
        {
            write(csock, "Serveur plein\n", 14);
            close(csock);
            pthread_mutex_unlock(&mtx);
            continue;
        }
        
        clients[idx] = csock;
        strncpy(client_ips[idx], inet_ntoa(client.sin_addr), 19);
        pthread_mutex_unlock(&mtx);

        printf("Nouveau client [%d] %s\n", idx, client_ips[idx]);
        
        pthread_t t;
        pthread_create(&t, NULL, handle_client, (void *)(long)idx);
        pthread_detach(t); // Le thread nettoiera ses propres ressources
    }
    
    return 0;
}