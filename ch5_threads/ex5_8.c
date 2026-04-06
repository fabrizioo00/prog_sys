/* Ex 5.8: Problème du rendez-vous avec sémaphores
 * a) T1 attend T2 à chaque itération (T1:2s, T2:4-9s aléatoire)
 * b) N threads avec rendez-vous, N passé en argument
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

int N;
sem_t *barriere;  // tableau de sémaphores pour rendez-vous 
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int arrived = 0;

void *thread_func(void *arg)
{
    int id = (long)arg;
    for (int i = 0; i < 10; i++) 
    {
        int duree = rand() % 5 + 1;
        printf("Thread %d: traitement %d (%ds)\n", id, i, duree);
        sleep(duree);

        //  barrière: attendre que tous les threads soient arrivés 
        pthread_mutex_lock(&mtx);
        arrived++;
        if (arrived == N) 
        {
            // dernier arrivé: libère tout le monde 
            arrived = 0;
            for (int j = 0; j < N - 1; j++)
                sem_post(&barriere[0]);
            pthread_mutex_unlock(&mtx);
        } 
        else 
        {
            pthread_mutex_unlock(&mtx);
            sem_wait(&barriere[0]);
        }
        printf("Thread %d: rendez-vous %d OK\n", id, i);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    N = (argc >= 2) ? atoi(argv[1]) : 2;
    srand(time(NULL));

    barriere = malloc(sizeof(sem_t));
    sem_init(&barriere[0], 0, 0);

    pthread_t *threads = malloc(N * sizeof(pthread_t));
    for (long i = 0; i < N; i++)
        pthread_create(&threads[i], NULL, thread_func, (void *)i);
    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    sem_destroy(&barriere[0]);
    free(barriere);
    free(threads);
    return 0;
}
