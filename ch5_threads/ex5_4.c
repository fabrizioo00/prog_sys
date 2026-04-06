/* Ex 5.4: T1⊂T2 check + interruption touche 'A' */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct 
{ 
    int *tab; 
    int n; 
} Tab;

typedef struct 
{ 
    Tab *t1; 
    Tab *t2; 
} InclusionArg;

void *genere(void *arg)
{
    Tab *t = (Tab *)arg;
    t->tab = malloc(t->n * sizeof(int));
    for (int i = 0; i < t->n; i++)
        t->tab[i] = rand() % 100;
    pthread_exit(NULL);
}


void *verifie_inclusion(void *arg)
{
    InclusionArg *a = (InclusionArg *)arg;
    for (int i = 0; i < a->t1->n; i++) 
    {
        int found = 0;
        for (int j = 0; j < a->t2->n; j++)
            if (a->t1->tab[i] == a->t2->tab[j]) 
            { 
                found = 1; 
                break; 
            }
        if (!found) pthread_exit((void *)0);
    }
    pthread_exit((void *)1);
}

void *attente_annulation(void *arg)
{
    char c;
    while ((c = getchar()) != 'A' && c != EOF);
    printf("Annulation par l'utilisateur !\n");
    exit(0);
}

int main(void)
{
    srand(time(NULL));
    Tab t1 = {NULL, 5}, t2 = {NULL, 20};
    pthread_t th1, th2, th_cancel;

    // génération parallèle 
    pthread_create(&th1, NULL, genere, &t1);
    pthread_create(&th2, NULL, genere, &t2);

    // thread d'annulation 
    pthread_create(&th_cancel, NULL, attente_annulation, NULL);
    pthread_detach(th_cancel);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    printf("T1: "); 
    for (int i = 0; i < t1.n; i++) 
        printf("%d ", t1.tab[i]);
    printf("\nT2: "); 
    for (int i = 0; i < t2.n; i++) 
        printf("%d ", t2.tab[i]);
    printf("\n");

    // vérification inclusion 
    InclusionArg ia = {&t1, &t2};
    pthread_t th3;
    long res;
    pthread_create(&th3, NULL, verifie_inclusion, &ia);
    pthread_join(th3, (void **)&res);
    printf("T1 %s T2 (complexité O(n*m))\n", res ? "⊂" : "⊄");

    free(t1.tab); free(t2.tab);
    return 0;
}
