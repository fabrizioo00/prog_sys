/* Ex 5.10: Producteurs/Consommateurs LIFO (pile de 10 octets) */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define TAILLE 10
unsigned char tampon[TAILLE];
int sommet = 0; /* index pile LIFO */
sem_t sem_places, sem_produits;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *producteur(void *arg)
{
    int id = (long)arg;
    for (int i = 0; i < 5; i++) 
    {
        unsigned char val = rand() % 256;
        sem_wait(&sem_places);
        pthread_mutex_lock(&mtx);
        tampon[sommet++] = val;
        printf("[P%d] produit %d (sommet=%d)\n", id, val, sommet);
        pthread_mutex_unlock(&mtx);
        sem_post(&sem_produits);
        sleep(rand() % 3 + 1);
    }
    pthread_exit(NULL);
}

void *consommateur(void *arg)
{
    int id = (long)arg;
    
    for (int i = 0; i < 5; i++) 
    {
        sem_wait(&sem_produits);
        pthread_mutex_lock(&mtx);
        unsigned char val = tampon[--sommet];
        printf("[C%d] consommé %d (sommet=%d)\n", id, val, sommet);
        pthread_mutex_unlock(&mtx);
        sem_post(&sem_places);
        sleep(rand() % 3 + 1);
    }
    pthread_exit(NULL);
}

int main(void)
{
    int N, M;
    printf("Nombre de producteurs : "); 
    scanf("%d", &N);
    printf("Nombre de consommateurs : "); 
    scanf("%d", &M);

    srand(time(NULL));
    
    sem_init(&sem_places, 0, TAILLE);
    sem_init(&sem_produits, 0, 0);

    pthread_t *prods = malloc(N * sizeof(pthread_t));
    pthread_t *cons = malloc(M * sizeof(pthread_t));

    for (long i = 0; i < N; i++)
        pthread_create(&prods[i], NULL, producteur, (void *)i);
    for (long i = 0; i < M; i++)
        pthread_create(&cons[i], NULL, consommateur, (void *)i);
    for (int i = 0; i < N; i++) 
        pthread_join(prods[i], NULL);
    for (int i = 0; i < M; i++) 
        pthread_join(cons[i], NULL);

    sem_destroy(&sem_places);
    sem_destroy(&sem_produits);
    free(prods); free(cons);
    return 0;
}
