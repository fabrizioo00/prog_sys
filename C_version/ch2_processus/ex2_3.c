#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int i;
    for (i = 0; i < 5; i++) 
    {
        pid_t pid = fork();
        if (pid == -1) 
        { 
            perror("fork"); 
            exit(1); 
        }
        if (pid == 0) 
        {
            printf("je suis le fils %d (PID=%d)\n", i + 1, getpid());
            break; // le fils ne continue pas la boucle 
        }
    }
    if (i == 5) 
    { 
        // père
        for (int j = 0; j < 5; j++) 
            wait(NULL);
        printf("je suis le père, tous les fils sont terminés\n");
    }
    return 0;
}
