#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = fork();
    if (pid == -1) 
    { 
        perror("fork"); 
        exit(1); 
    }
    if (pid == 0)
        printf("je suis le fils (PID=%d)\n", getpid());
    else
        printf("je suis le père (PID=%d)\n", getpid());
    return 0;
}
