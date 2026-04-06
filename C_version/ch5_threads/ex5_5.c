/* Ex 5.5: Compteur global + 2 threads (incr + affichage) */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int compt = 0;
int limite;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *incrementeur(void *arg)
{
    srand(time(NULL));
    while (1) 
    {
        pthread_mutex_lock(&mtx);
        if (compt >= limite) 
        { 
            pthread_mutex_unlock(&mtx); 
            break; 
        }
        compt++;
        pthread_mutex_unlock(&mtx);
        sleep(rand() % 5 + 1);
    }
    pthread_exit(NULL);
}

void *afficheur(void *arg)
{
    while (1) 
    {
        sleep(2);
        pthread_mutex_lock(&mtx);
        printf("%d\n", compt);
        if (compt >= limite) 
        { 
            pthread_mutex_unlock(&mtx); 
            break; 
        }
        pthread_mutex_unlock(&mtx);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc != 2) 
    { 
        fprintf(stderr, "Usage: %s limite\n", argv[0]); 
        return 1; 
    }
    limite = atoi(argv[1]);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, incrementeur, NULL);
    pthread_create(&t2, NULL, afficheur, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
