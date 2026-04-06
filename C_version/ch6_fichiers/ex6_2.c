/* Ex 6.2: Lister fichiers > 1Mo avec UID du propriétaire */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2) 
    {
        fprintf(stderr, "Usage: %s rep1 [rep2 ...]\n", argv[0]);
        return 1;
    }
    
    for (int i = 1; i < argc; i++) 
    {
        DIR *dir = opendir(argv[i]);
        if (!dir) 
        { 
            perror(argv[i]); 
            continue; 
        }
        
        struct dirent *ent;
        while ((ent = readdir(dir))) 
        {
            char path[512];
            //  Construit le chemin complet pour stat() 
            snprintf(path, sizeof(path), "%s/%s", argv[i], ent->d_name);
            
            struct stat st;
            // 1024 * 1024 = 1 048 576 octets (1 MiB) 
            if (stat(path, &st) == 0 && S_ISREG(st.st_mode) && st.st_size > 1048576) 
            {
                // Cast en (long) pour éviter les warnings sur différentes architectures
                printf("%s  taille=%ld octets  UID=%u\n", path, (long)st.st_size, (unsigned int)st.st_uid);
            }
        }
        closedir(dir);
    }
    return 0;
}