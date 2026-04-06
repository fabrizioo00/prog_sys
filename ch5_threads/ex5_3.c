/* Ex 5.3: Génération parallèle tableau + lecture x + recherche */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct 
{ 
    int *tab; 
    int n; 
    int x; 
} TypeTableau;

void *genere(void *arg)
{
    TypeTableau *t = (TypeTableau *)arg;
    srand(time(NULL));
    t->tab = malloc(t->n * sizeof(int));
    for (int i = 0; i < t->n; i++)
        t->tab[i] = rand() % 100;
    pthread_exit(NULL);
}

void *recherche(void *arg)
{
    TypeTableau *t = (TypeTableau *)arg;
    for (int i = 0; i < t->n; i++)
        if (t->tab[i] == t->x)
            pthread_exit((void *)1);
    pthread_exit((void *)0);
}

int main(void)
{
    TypeTableau tt;
    tt.n = 20;
    pthread_t t1;

    // thread génère le tableau en parallèle 
    pthread_create(&t1, NULL, genere, &tt);

    //  pendant ce temps, le main lit x 
    printf("Entrez x : ");
    scanf("%d", &tt.x);

    pthread_join(t1, NULL);

    printf("Tableau : ");
    for (int i = 0; i < tt.n; i++) 
        printf("%d ", tt.tab[i]);
    printf("\n");

    //  thread de recherche 
    pthread_t t2;
    long res; // long parce que (void*) 8 octets
    pthread_create(&t2, NULL, recherche, &tt);
    pthread_join(t2, (void **)&res);
    printf("%d %s dans le tableau\n", tt.x, res ? "trouvé" : "non trouvé");
    free(tt.tab);
    return 0;
}
