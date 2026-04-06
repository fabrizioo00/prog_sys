#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s repertoire_destination\n", argv[0]);
        return 1;
    }
    pid_t pid = fork();
    if (pid == -1) 
    { 
        perror("fork"); 
        exit(1); 
    }
    if (pid == 0) 
    {
        execlp("cp", "cp", "-r", ".", argv[1], NULL);
        perror("execlp cp");
        exit(1);
    }
    wait(NULL);
    printf("Copie terminée dans %s\n", argv[1]);
    return 0;
}
