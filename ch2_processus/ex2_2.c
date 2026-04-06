#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t p1 = fork();
    if (p1 == -1) 
    { 
        perror("fork"); 
        exit(1); 
    }
    if (p1 == 0) 
    {
        printf("je suis le fils 1 (PID=%d)\n", getpid());
        exit(0);
    }
    pid_t p2 = fork();
    if (p2 == -1) 
    { 
        perror("fork"); 
        exit(1); 
    }
    if (p2 == 0) 
    {
        printf("je suis le fils 2 (PID=%d)\n", getpid());
        exit(0);
    }
    printf("je suis le père (PID=%d)\n", getpid());
    wait(NULL);
    wait(NULL);
    return 0;
}
