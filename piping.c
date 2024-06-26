#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

// int main(int argc, char **argv)
// {
//     int fd[2];
//     int id;
//     int x;
//     int y;
//     // fd[0] - read
//     // fd[1] - write
//     if (pipe(fd) == -1)
//     {
//         printf("An error with the pipe.\n");
//         return (1);
//     }
//     id = fork();
//     if (id == -1)
//     {
//         printf("An error with fork");
//         return(2);
//     }
//     if (id == 0)
//     {
//         close(fd[0]);
//         printf("Input a number: ");
//         scanf("%d", &x);
//         write(fd[1], &x, sizeof(int));
//         close(fd[1]);
//     }
//     else // Parent Process
//     {
//         close(fd[1]);
//         read(fd[0], &y, sizeof(int));
//         close(fd[0]);
//         printf("Got from child process %d\n", y);
//     }
//     return(0);
// }

// Playing with fork
int main(int argc, char **argv)
{
    int arr[] = { 1, 2, 3, 4, 1, 2, 7, 7};
    int arrSize = sizeof(arr)/sizeof(int);
    int fd[2];
    int start;
    int id;
    int end;
    int sum;
    int i;

    if (pipe(fd) == -1)
        return 1;
    
    id = fork();

    if (id == -1)
        return 2;
    
    if (id == 0)
    {
        start = 0;
        end = arrSize/2;
    }
    else
    {
        start = arrSize/2;
        end = arrSize;
    }
    sum = 0;
    i = start;
    while (i < end)
    {
        sum = sum + arr[i];
        i++;
    }
    printf("Calculated partial sum: %d.\n", sum);
    if (id == 0)
    {
        close(fd[0]);
        write(fd[1], &sum, sizeof(sum));
        close(fd[1]);

    }
    else
    {
        int sumfchild;
        int totalSum;
        close(fd[1]);
        read(fd[0], &sumfchild, sizeof(sumfchild));
        close(fd[0]);
        totalSum = sum + sumfchild;
        printf("Total sum is %d\n", totalSum);
        wait(NULL);
    }

    return(0);
}
