#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUF 256

int main(void)
{
    int tube[2];
    pipe(tube);

    pid_t pid = fork();
    if (pid == -1) 
    { 
        perror("fork"); 
        exit(1); 
    }

    if (pid == 0) 
    {
        close(tube[1]);
        char env_var[64];
        sprintf(env_var, "TUBE_FD=%d", tube[0]);
        putenv(env_var);
        char *args[] = {"ex4_4_fils", NULL};
        execv("./ex4_4_fils", args);
        perror("execv");
        exit(1);
    }
    close(tube[0]);
    char msg[BUF] = "Message via variable d'environnement !";
    write(tube[1], msg, BUF);
    close(tube[1]);
    wait(NULL);
    return 0;
}
