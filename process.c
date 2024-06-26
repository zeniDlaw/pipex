#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(void)
{
    int id;
    id = fork();
    printf("Current ID: %d, parent ID: %d.\n", getpid(), getppid());
    return(0);
}
