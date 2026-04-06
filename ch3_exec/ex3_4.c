#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    char rep[256];
    while (1) 
    {
        printf("Répertoire destination (q pour quitter) : ");
        scanf("%s", rep);
        if (strcmp(rep, "q") == 0) 
            break;
        pid_t pid = fork();
        if (pid == -1) 
        { 
            perror("fork"); 
            exit(1); 
        }
        if (pid == 0) 
        {
            execlp("cp", "cp", "-r", ".", rep, NULL);
            perror("execlp cp");
            exit(1);
        }
        wait(NULL);
        printf("Copié dans %s\n", rep);
    }
    return 0;
}
