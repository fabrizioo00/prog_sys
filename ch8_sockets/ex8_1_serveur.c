/* Ex 8.1: Serveur TCP/IP - base de données produits
 * a-g) Gère structure produit, chargement BDD, recherche, commandes clients
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <time.h>
#define BUF 256
#define MAX_PROD 100

typedef struct 
{ 
    char nom[50]; 
    float prix; 
} Produit;

Produit bdd[MAX_PROD];
int nb_prod = 0;

void charger_bdd(const char *fichier)
{
    FILE *f = fopen(fichier, "r");
    if (!f) 
    { 
        perror("bdd"); 
        exit(1); 
    }
    while (fscanf(f, "%s %f", bdd[nb_prod].nom, &bdd[nb_prod].prix) == 2)
        nb_prod++;
    fclose(f);
}

Produit *chercher(const char *nom)
{
    for (int i = 0; i < nb_prod; i++)
        if (strcmp(bdd[i].nom, nom) == 0) return &bdd[i];
    return NULL;
}

void traite_client(int sock)
{
    char buf[BUF], nom[50], nom_client[50]; 
    int qte;
    float total = 0;

    // Demande du nom du client 
    write(sock, "Veuillez entrer votre nom : ", 28);
    int n_nom = read(sock, nom_client, 50);
    if (n_nom > 0) 
    {
        nom_client[n_nom] = '\0';
        nom_client[strcspn(nom_client, "\r\n")] = 0; // Nettoyage du retour à la ligne
    } 
    else 
    {
        strcpy(nom_client, "Inconnu");
    }

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char fname[100];
    sprintf(fname, "/tmp/commande_%04d%02d%02d_%02d%02d%02d.txt",
            tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
            tm->tm_hour, tm->tm_min, tm->tm_sec);
    FILE *fc = fopen(fname, "w");

    if (fc) fprintf(fc, "Client : %s\n---\n", nom_client);

    sprintf(buf, "Produits: ");
    for (int i = 0; i < nb_prod; i++) 
    {
        char tmp[60];
        sprintf(tmp, "%s(%.2f€) ", bdd[i].nom, bdd[i].prix);
        strcat(buf, tmp);
    }
    strcat(buf, "\nProduit (fin pour terminer): ");
    write(sock, buf, BUF);

    while (1) 
    {
        int n = read(sock, buf, BUF);
        if (n <= 0) break;
        buf[strcspn(buf, "\r\n")] = 0;
        if (strcmp(buf, "fin") == 0) break;
        sscanf(buf, "%s %d", nom, &qte);
        Produit *p = chercher(nom);
        if (p) 
        {
            float prix = p->prix * qte;
            total += prix;
            sprintf(buf, "%s x%d = %.2f€ (total=%.2f€)\nProduit: ", nom, qte, prix, total);
            if (fc) fprintf(fc, "%s %d %.2f\n", nom, qte, prix);
        } 
        else 
        {
            sprintf(buf, "Produit '%s' non trouvé\nProduit: ", nom);
        }
        write(sock, buf, BUF);
    }
    sprintf(buf, "Total commande: %.2f€\n", total);
    write(sock, buf, BUF);
    if (fc) 
    { 
        fprintf(fc, "TOTAL: %.2f\n", total); 
        fclose(fc); 
    }
    close(sock);
}

int main(int argc, char *argv[])
{
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s fichier_bdd\n", argv[0]);
        return 1;
    }
    charger_bdd(argv[1]);
    printf("%d produits chargés\n", nb_prod);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1; setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in addr = {.sin_family=AF_INET, .sin_port=htons(33016),
                               .sin_addr.s_addr=htonl(INADDR_ANY)};
    bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    listen(sock, 5);
    printf("Serveur en écoute sur le port 33016\n");

    while (1) 
    {
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int csock = accept(sock, (struct sockaddr*)&client, &len);
        if (csock < 0) continue;
        printf("Client: %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        pid_t pid = fork();
        if (pid == 0)
        { 
            close(sock); 
            traite_client(csock); 
            exit(0); 
        }
        close(csock);
        waitpid(-1, NULL, WNOHANG);
    }

    return 0;
}