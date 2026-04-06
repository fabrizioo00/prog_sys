#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) 
{
    int n = atoi(argv[1]), k = atoi(argv[2]);
    // cas de base
    int res = (k < 0 || k > n) ? 0 : ((k == 0 || k == n) ? 1 : 0);

    if (res == 0) 
    { 
        // Si ce n'est pas un cas de base, on lance les calculs
        char sn[16], sk1[16], sk2[16], f1[32], f2[32];
        sprintf(sn, "%d", n - 1);
        sprintf(sk1, "%d", k - 1);
        sprintf(sk2, "%d", k);

        // Lancement des deux fils
        pid_t p1 = fork();
        if (p1 == 0) 
        { 
            execl(argv[0], argv[0], sn, sk1, "fils", NULL); 
            exit(1); 
        }
        
        pid_t p2 = fork();
        if (p2 == 0) 
        { 
            execl(argv[0], argv[0], sn, sk2, "fils", NULL); 
            exit(1); 
        }

        wait(NULL); wait(NULL); // On attend la fin des deux fils

        // Récupération des résultats via les fichiers temporaires
        int r1 = 0, r2 = 0;
        sprintf(f1, "/tmp/%d", p1);
        sprintf(f2, "/tmp/%d", p2);
        
        FILE *file1 = fopen(f1, "r"), *file2 = fopen(f2, "r");
        if (file1) 
        { 
            fscanf(file1, "%d", &r1); 
            fclose(file1); 
            remove(f1); 
        }
        if (file2) 
        { 
            fscanf(file2, "%d", &r2); 
            fclose(file2);
            remove(f2); 
        }
        
        res = r1 + r2;
    }

    // Le chef d'orchestre (argc == 3) affiche, les fils écrivent en fichier
    if (argc == 3) 
    {
        printf("%d\n", res);
    } 
    else 
    {
        char my_file[32];
        sprintf(my_file, "/tmp/%d", getpid());
        FILE *f = fopen(my_file, "w");
        if (f) 
        { 
            fprintf(f, "%d", res); 
            fclose(f);
        }
    }

    return 0;
}