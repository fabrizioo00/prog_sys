/* Ex 7.2 - affiche.c: attend SIGUSR1, puis lit et affiche /tmp/entier.txt */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int recu = 0;

void handler(int sig)
{
    if (sig == SIGUSR1) recu = 1;
}

int main(void)
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);

    printf("Mon PID = %d. En attente de SIGUSR1...\n", getpid());
    while (!recu) pause();

    FILE *f = fopen("/tmp/entier.txt", "r");
    int val;
    fscanf(f, "%d", &val);
    fclose(f);
    printf("Valeur reçue : %d\n", val);
    return 0;
}
