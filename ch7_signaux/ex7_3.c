/* Ex 7.3: 5 fils while(1) + menu père (endormir/réveiller/terminer)
 * b) Les fils affichent un message quand ils sont tués (SIGTERM handler) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int num_fils_global;

void handler_fils(int sig)
{
    printf("[fils %d] je suis terminé !\n", num_fils_global);
    exit(0);
}

void handler_pere(int sig)
{
    printf("[père] je suis terminé !\n");
    exit(0);
}

int main(void)
{
    pid_t pids[5];
    for (int i = 0; i < 5; i++) 
    {
        pids[i] = fork();
        if (pids[i] == 0) 
        {
            num_fils_global = i + 1;
            struct sigaction sa;
            sa.sa_handler = handler_fils;
            sigemptyset(&sa.sa_mask);
            sa.sa_flags = 0;
            sigaction(SIGTERM, &sa, NULL);
            while (1) sleep(1);
        }
    }
    // pere
    struct sigaction sa;
    sa.sa_handler = handler_pere;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGTERM, &sa, NULL);

    int choix, num;
    while (1) 
    {
        printf("\n1=Endormir 2=Réveiller 3=Terminer 0=Quitter\n> ");
        scanf("%d", &choix);
        if (choix == 0) break;
        printf("Numéro du fils (1-5) : "); scanf("%d", &num);
        if (num < 1 || num > 5) continue;
        switch (choix) 
        {
            case 1: 
                kill(pids[num-1], SIGSTOP); 
                break;
            case 2: 
                kill(pids[num-1], SIGCONT); 
                break;
            case 3: 
                kill(pids[num-1], SIGTERM);
                waitpid(pids[num-1], NULL, 0); 
                break;
        }
    }
    for (int i = 0; i < 5; i++) 
    {
        kill(pids[i], SIGTERM);
        waitpid(pids[i], NULL, WNOHANG);
    }
    return 0;
}
