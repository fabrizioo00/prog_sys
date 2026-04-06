#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF 256

int main(void)
{
    char *env = getenv("TUBE_FD");
    if (!env) 
    {
        fprintf(stderr, "Variable TUBE_FD non définie\n");
        return 1;
    }
    int fd = atoi(env);
    char buffer[BUF];
    read(fd, buffer, BUF);
    printf("Fils a reçu : %s\n", buffer);
    close(fd);
    return 0;
}
