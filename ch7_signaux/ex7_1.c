/* Ex 7.1: Père contrôle fils (s=stop, r=resume, q=quit) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid = fork();
    if (pid == -1) 
    { 
        perror("fork"); 
        exit(1); 
    }

    if (pid == 0) 
    { 
        // fils: boucle infinie 
        while (1) 
        {
            printf("[fils %d] travaille...\n", getpid());
            sleep(1);
        }
    }
    // père: menu 
    char c;
    printf("Fils PID=%d. Commandes: s=stop r=resume q=quit\n", pid);
    while (1) 
    {
        printf("> ");
        scanf(" %c", &c);
        switch (c) 
        {
            case 's': 
                kill(pid, SIGSTOP); 
                printf("Fils stoppé\n"); 
                break;
            case 'r': 
                kill(pid, SIGCONT); 
                printf("Fils repris\n"); 
                break;
            case 'q': 
                kill(pid, SIGTERM); 
                wait(NULL);
                printf("Fils tué\n"); 
                return 0;
        }
    }
}
