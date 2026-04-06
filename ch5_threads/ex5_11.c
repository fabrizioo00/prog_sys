/* Ex 5.11: Lecteurs/Rédacteurs – famine des écrivains */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define DB_SIZE 15
unsigned char base[DB_SIZE];
int nb_lecteurs = 0;
pthread_mutex_t mtx_lecteurs = PTHREAD_MUTEX_INITIALIZER;
sem_t sem_ecrivain; /* contrôle accès exclusif pour écriture */

void *lecteur(void *arg)
{
    int id = (long)arg;
    for (int i = 0; i < 5; i++) 
    {
        pthread_mutex_lock(&mtx_lecteurs);
        nb_lecteurs++;
        if (nb_lecteurs == 1) 
            sem_wait(&sem_ecrivain);
        pthread_mutex_unlock(&mtx_lecteurs);

        int pos = rand() % DB_SIZE;
        printf("[L%d] lit base[%d] = %d\n", id, pos, base[pos]);

        pthread_mutex_lock(&mtx_lecteurs);
        nb_lecteurs--;
        if (nb_lecteurs == 0) 
            sem_post(&sem_ecrivain);
        pthread_mutex_unlock(&mtx_lecteurs);

        sleep(rand() % 3 + 1);
    }
    pthread_exit(NULL);
}

void *redacteur(void *arg)
{
    int id = (long)arg;
    
    for (int i = 0; i < 3; i++) 
    {
        sem_wait(&sem_ecrivain);
        int pos = rand() % DB_SIZE;
        unsigned char val = rand() % 256;
        base[pos] = val;
        printf("[R%d] écrit base[%d] = %d\n", id, pos, val);
        sem_post(&sem_ecrivain);
        sleep(rand() % 10 + 1);
    }
    pthread_exit(NULL);
}

int main(void)
{
    int N, M;
    printf("Nombre de lecteurs : "); 
    scanf("%d", &N);
    printf("Nombre de rédacteurs : "); 
    scanf("%d", &M);

    srand(time(NULL));

    memset(base, 0, DB_SIZE);
    sem_init(&sem_ecrivain, 0, 1);

    pthread_t *lect = malloc(N * sizeof(pthread_t));
    pthread_t *red = malloc(M * sizeof(pthread_t));
    for (long i = 0; i < N; i++)
        pthread_create(&lect[i], NULL, lecteur, (void *)i);
    for (long i = 0; i < M; i++)
        pthread_create(&red[i], NULL, redacteur, (void *)i);
    for (int i = 0; i < N; i++) 
        pthread_join(lect[i], NULL);
    for (int i = 0; i < M; i++) 
        pthread_join(red[i], NULL);

    sem_destroy(&sem_ecrivain);
    free(lect); free(red);
    return 0;
}
