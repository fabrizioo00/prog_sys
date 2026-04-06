#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUF 256

int main(int argc, char *argv[])
{
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s fichier\n", argv[0]);
        return 1;
    }
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
        //  fils: saisit mot, écrit dans tube via stdout 
        close(tube[0]);
        char mot[BUF];
        fprintf(stderr, "Entrez un mot : ");
        scanf("%s", mot);
        dup2(tube[1], STDOUT_FILENO);
        close(tube[1]);
        printf("%s", mot);
        fflush(stdout);
    } 
    else 
    { 
        //  père: lit mot depuis tube via stdin, cherche dans fichier 
        close(tube[1]);
        dup2(tube[0], STDIN_FILENO);
        close(tube[0]);
        char mot[BUF], buf[BUF];
        scanf("%s", mot);
        wait(NULL);
        FILE *f = fopen(argv[1], "r");
        int res = 0;
        if (f) 
        {
            while (fscanf(f, "%s", buf) == 1)
            {
                if (strcmp(buf, mot) == 0) 
                { 
                    res = 1; 
                    break; 
                }
            }

            fclose(f);
        }
        printf("Mot '%s' : %s\n", mot, res ? "trouvé" : "non trouvé");
    }
    return 0;
}
