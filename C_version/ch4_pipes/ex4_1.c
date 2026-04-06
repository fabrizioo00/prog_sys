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
    int tube_mot[2], tube_res[2];  // fils→père, père→fils 
    pipe(tube_mot);
    pipe(tube_res);

    pid_t pid = fork();
    if (pid == -1) 
    { 
        perror("fork"); 
        exit(1); 
    }

    if (pid == 0) 
    { 
        
        close(tube_mot[0]); 
        close(tube_res[1]);
        char mot[BUF];
        printf("Entrez un mot : ");
        scanf("%s", mot);
        write(tube_mot[1], mot, BUF);
        int res;
        read(tube_res[0], &res, sizeof(int));
        printf("%d\n", res);
        close(tube_mot[1]); 
        close(tube_res[0]);
    } 
    else 
    { 
        
        close(tube_mot[1]);
        close(tube_res[0]);
        char mot[BUF], buf[BUF];
        read(tube_mot[0], mot, BUF);
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
        write(tube_res[1], &res, sizeof(int));
        close(tube_mot[0]); close(tube_res[1]);
        wait(NULL);
    }
    return 0;
}
