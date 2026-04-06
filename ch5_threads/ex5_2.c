/* Ex 5.2: Thread qui alloue et retourne un tableau aléatoire (0-99) */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 10

void *genere_tab(void *arg)
{
    int *tab = malloc(N * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < N; i++)
        tab[i] = rand() % 100;
    pthread_exit((void *)tab);
}

int main(void)
{
    pthread_t t;
    int *tab;
    pthread_create(&t, NULL, genere_tab, NULL);
    pthread_join(t, (void **)&tab);
    for (int i = 0; i < N; i++)
        printf("tab[%d] = %d\n", i, tab[i]);
    free(tab);
    return 0;
}
