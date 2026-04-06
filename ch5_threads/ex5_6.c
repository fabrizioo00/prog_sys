/* Ex 5.6: Lissage tableau de N=100 doubles + affichage toutes les 4s */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define N 100
double tableau[N];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
volatile int running = 1;

void *lissage(void *arg)
{
    srand(time(NULL));
    while (running) 
    {
        pthread_mutex_lock(&mtx);
        double tmp[N];
        tmp[0] = tableau[0];
        tmp[N-1] = tableau[N-1];
        for (int i = 1; i < N - 1; i++)
            tmp[i] = (tableau[i-1] + tableau[i] + tableau[i+1]) / 3.0;
        for (int i = 1; i < N - 1; i++)
            tableau[i] = tmp[i];
        pthread_mutex_unlock(&mtx);
        sleep(rand() % 3 + 1);
    }
    pthread_exit(NULL);
}

void *affichage(void *arg)
{
    int iter = 0;
    while (iter < 5) 
    { 
        //  5 affichages puis arrêt 
        sleep(4);
        pthread_mutex_lock(&mtx);
        printf("---Itération %d--- \n", ++iter);
        for (int i = 0; i < N; i++) 
        {
            printf("%.2f ", tableau[i]);
            if ((i + 1) % 10 == 0) 
                printf("\n");
        }
        pthread_mutex_unlock(&mtx);
    }
    running = 0;
    pthread_exit(NULL);
}

int main(void)
{
    srand(time(NULL));
    tableau[0] = 0; tableau[N-1] = 0;
    for (int i = 1; i < N - 1; i++)
        tableau[i] = (double)(rand() % 10000) / 100.0;

    pthread_t t1, t2;
    pthread_create(&t1, NULL, lissage, NULL);
    pthread_create(&t2, NULL, affichage, NULL);
    pthread_join(t2, NULL);
    pthread_join(t1, NULL);
    return 0;
}
