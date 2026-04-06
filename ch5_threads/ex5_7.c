/* Ex 5.7: Deux threads T1 et T2 appliquent f1(x)=1/4*(x-1)^2 et f2(x)=1/6*(x-2)^2 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

double u = 1.0;
int compteur = 0;
int limite = 20;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *thread_f1(void *arg)
{
    while (1) 
    {
        pthread_mutex_lock(&mtx);
        if (compteur >= limite) 
        { 
            pthread_mutex_unlock(&mtx); 
            break; 
        }
        compteur++;
        u = 0.25 * (u - 1) * (u - 1);
        printf("[T1] iter=%d u=%.6f\n", compteur, u);
        pthread_mutex_unlock(&mtx);
        sleep(rand() % 5 + 1);
    }
    pthread_exit(NULL);
}

void *thread_f2(void *arg)
{
    
    while (1) 
    {
        pthread_mutex_lock(&mtx);
        if (compteur >= limite) 
        { 
            pthread_mutex_unlock(&mtx); 
            break; 
        }
        compteur++;
        u = (1.0 / 6.0) * (u - 2) * (u - 2);
        printf("[T2] iter=%d u=%.6f\n", compteur, u);
        pthread_mutex_unlock(&mtx);
        sleep(rand() % 5 + 1);
    }
    pthread_exit(NULL);
}

int main(void)
{
    srand(time(NULL));
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread_f1, NULL);
    pthread_create(&t2, NULL, thread_f2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Valeur finale : u=%.6f après %d itérations\n", u, compteur);

    // Libération du mutex
    pthread_mutex_destroy(&mtx);
    return 0;
}
