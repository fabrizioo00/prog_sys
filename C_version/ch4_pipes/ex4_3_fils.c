#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF 256

int main(int argc, char *argv[])
{
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s fd_lecture\n", argv[0]);
        return 1;
    }
    int fd = atoi(argv[1]);
    char buffer[BUF];
    read(fd, buffer, BUF);
    printf("Fils a reçu : %s\n", buffer);
    close(fd);
    return 0;
}
