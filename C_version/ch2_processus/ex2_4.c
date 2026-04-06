#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int num_fils;

int main(void)
{
    int i;
    for (i = 0; i < 5; i++) 
    {
        num_fils = i + 1;
        pid_t pid = fork();
        if (pid == -1) 
        { 
            perror("fork"); 
            exit(1); 
        }
        if (pid == 0) 
        {
            printf("je suis le fils %d (PID=%d)\n", num_fils, getpid());
            break;
        }
    }
    if (i == 5) 
    {
        for (int j = 0; j < 5; j++) 
            wait(NULL);
        printf("je suis le père (PID=%d)\n", getpid());
    }
    return 0;
}
