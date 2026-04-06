/* Ex 6.3: a) Sauvegarder tableau en binaire, b) Charger sans connaître n */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void sauvegarder(void)
{
    int n;
    printf("Nombre d'éléments : "); scanf("%d", &n);
    int *tab = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) 
    {
        printf("tab[%d] = ", i); scanf("%d", &tab[i]);
    }
    
    int fd = open("tableau.bin", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (fd < 0) 
    { 
        perror("open"); 
        free(tab); 
        return; 
    }
    write(fd, tab, n * sizeof(int));
    close(fd);
    free(tab);
    printf("Sauvegardé dans tableau.bin\n");
}

void charger(void)
{
    struct stat st;
    if (stat("tableau.bin", &st) != 0) 
    { 
        perror("stat"); 
        return; 
    }
    int n = st.st_size / sizeof(int);
    int *tab = malloc(n * sizeof(int));
    int fd = open("tableau.bin", O_RDONLY);
    if (fd < 0) 
    { 
        perror("open"); 
        free(tab); 
        return; 
    }
    read(fd, tab, n * sizeof(int));
    close(fd);
    printf("Chargé %d éléments :\n", n);
    for (int i = 0; i < n; i++)
        printf("tab[%d] = %d\n", i, tab[i]);
    free(tab);
}

int main(int argc, char *argv[])
{
    if (argc == 2 && argv[1][0] == 'c')
        charger();
    else
        sauvegarder();
    return 0;
}
