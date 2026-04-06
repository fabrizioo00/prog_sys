/* Ex 5.9: Émetteur/Récepteur avec sémaphores
 * L'émetteur dépose un octet, le récepteur le lit.
 * Deux sémaphores: plein (0 init) et vide (1 init).
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

unsigned char donnee;
sem_t sem_plein, sem_vide;

void *emetteur(void *arg)
{
    
    for (int i = 0; i < 10; i++) 
    {
        unsigned char val = rand() % 256;
        sem_wait(&sem_vide);    // attend que le récepteur ait lu 
        donnee = val;
        printf("[E] déposé: %d\n", val);
        sem_post(&sem_plein);   // signale au récepteur 
        sleep(rand() % 3 + 1);
    }
    pthread_exit(NULL);
}

void *recepteur(void *arg)
{

    for (int i = 0; i < 10; i++) 
    {
        sem_wait(&sem_plein);   // attend un nouvel octet 
        printf("[R] lu: %d\n", donnee);
        sem_post(&sem_vide);    // signale que c'est lu 
        sleep(rand() % 3 + 1);
    }
    pthread_exit(NULL);
}

int main(void)
{
    srand(time(NULL));
    sem_init(&sem_plein, 0, 0);
    sem_init(&sem_vide, 0, 1);
    pthread_t te, tr;
    pthread_create(&te, NULL, emetteur, NULL);
    pthread_create(&tr, NULL, recepteur, NULL);
    pthread_join(te, NULL);
    pthread_join(tr, NULL);
    sem_destroy(&sem_plein);
    sem_destroy(&sem_vide);
    return 0;
}
