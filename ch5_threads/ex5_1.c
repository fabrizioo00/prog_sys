/* Ex 5.1: Thread qui affiche un tableau d'entiers passé en paramètre */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct 
{ 
    int *tab; 
    int n;
     
} TabData;

void *affiche_tab(void *arg)
{
    TabData *d = (TabData *)arg;
    
    for (int i = 0; i < d->n; i++)
        printf("tab[%d] = %d\n", i, d->tab[i]);
    pthread_exit(NULL);
}

int main(void)
{
    int tab[] = {10, 20, 30, 40, 50};
    TabData d = {tab, 5};
    pthread_t t;
    pthread_create(&t, NULL, affiche_tab, &d);
    pthread_join(t, NULL);
    return 0;
}
