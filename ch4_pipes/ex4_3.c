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
        // fils: lance ex4_3_fils avec descripteurs en args 
        close(tube[1]);
        char fd_str[16];
        sprintf(fd_str, "%d", tube[0]);
        char *args[] = {"ex4_3_fils", fd_str, NULL};
        execv("./ex4_3_fils", args);
        perror("execv");
        exit(1);
    }
    // père: envoie un message dans le tube 
    close(tube[0]);
    char msg[BUF] = "Bonjour";
    write(tube[1], msg, BUF);
    close(tube[1]);
    wait(NULL);
    return 0;
}
