/* Ex 7.4: Tableau dynamique + SIGSEGV: resaisir l'index en cas d'erreur */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

int *tab;
int n, idx;
sigjmp_buf env;

void handler(int sig)
{
    if (sig == SIGSEGV) 
    {
        printf("Erreur de segmentation ! Resaisissez i.\n");
        siglongjmp(env, 1);
    }
}

int main(void)
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGSEGV, &sa, NULL);

    printf("Nombre d'éléments n : "); scanf("%d", &n);
    tab = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) 
    {
        printf("tab[%d] = ", i); scanf("%d", &tab[i]);
    }

    sigsetjmp(env, 1);
    printf("Indice i à afficher : "); scanf("%d", &idx);
    printf("tab[%d] = %d\n", idx, tab[idx]);

    free(tab);
    return 0;
}
