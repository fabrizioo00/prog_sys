#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(void)
{
    time_t debut = time(NULL);


    pid_t p1 = fork();
    if (p1 == -1) 
    { 
        perror("fork"); 
        exit(1); 
    }
    if (p1 == 0) 
    {
        srand(getpid());
        int s = rand() % 10 + 1;
        printf("fils 1 dort %d secondes\n", s);
        sleep(s);
        exit(0);
    }
    pid_t p2 = fork();
    if (p2 == -1) 
    { 
        perror("fork"); 
        exit(1); 
    }
    if (p2 == 0) 
    {
        srand(getpid());
        int s = rand() % 10 + 1;
        printf("fils 2 dort %d secondes\n", s);
        sleep(s);
        exit(0);
    }
    wait(NULL);
    wait(NULL);
    printf("durée totale : %ld secondes\n", time(NULL) - debut);
    return 0;
}
