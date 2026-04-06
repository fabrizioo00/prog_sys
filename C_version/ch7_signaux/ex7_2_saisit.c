/* Ex 7.2 - saisit.c: saisit un int, enregistre dans /tmp/entier.txt,
 * envoie SIGUSR1 au programme affiche.c (PID passé en argument) 
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s pid_affiche\n", argv[0]);
        return 1;
    }
    int val;
    printf("Entrez un entier : "); 
    scanf("%d", &val);
    FILE *f = fopen("/tmp/entier.txt", "w");
    fprintf(f, "%d", val);
    fclose(f);
    kill(atoi(argv[1]), SIGUSR1);
    printf("Signal envoyé au PID %s\n", argv[1]);
    return 0;
}
