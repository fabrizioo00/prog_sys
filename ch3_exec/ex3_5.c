#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    char nom[256];
    while (1) 
    {
        printf("Fichier à ouvrir (q pour quitter) : ");
        scanf("%s", nom);
        if (strcmp(nom, "q") == 0) 
            break;
        pid_t pid = fork();
        if (pid == -1) 
        { 
            perror("fork"); 
            exit(1); 
        }
        if (pid == 0) 
        {
            execl("/usr/bin/emacs", "emacs", nom, NULL);
            perror("execl emacs");
            exit(1);
        }
        wait(NULL);
    }
    return 0;
}
