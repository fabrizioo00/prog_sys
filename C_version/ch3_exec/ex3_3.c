#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    char nom[256];
    printf("Nom du fichier à ouvrir : ");
    scanf("%s", nom);
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
    return 0;
}
