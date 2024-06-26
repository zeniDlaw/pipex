#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


// Simple message from the Parent and the child process.
// int main(void)
// {
//     int f;

//     f = fork();

//     if (f < 0)
//         printf("Error while forking");
//     else if (f != 0)
//         printf("This is the Parent process and my id is: %d\n",getpid());
//     else
//         printf("This is the Child process and my ID is: %d\n",getpid());
//     return(0);
// }

// Parent Child Communication
// int main(void)
// {
//     pid_t pid;
//     int fd[2];
//     char message[38];

//     if (pipe(fd) == -1)
//     {
//         perror("An error with the pipe\n");
//         return (1);
//     }

//     pid = fork();
//     if (pid < 0)
//         perror("Forking error.\n");
//     else if (pid != 0)
//     {
//         close(fd[0]);
//         if (write(fd[1], "This is the message from the Parent", 37) == -1)
//             perror("Cannot Write");
//         close(fd[1]);
//         wait(NULL);
//     }
//     else
//     {
//         close(fd[1]);
//         if (read(fd[0], message, 37) == -1)
//             perror("Cannot Read");  
//         close(fd[0]);
//         message[37] = '\0';
//         printf("%s",message);  
//     }
//     return(0);
// }

// Multiple Children
// int main()
// {
//     pid_t pid;

//     pid = fork();

//     if (pid < 0)
//         perror("Forking Failed");
//     else if (pid != 0)
//     {
//         printf("Hey I am the Parent Process my PID is: %d.\n", getpid());
//         wait(NULL);
//     }
//     else
//     {
//         printf("I am the Child Process my PID is: %d.\n", getpid());
//         fork();
//         printf("I am another Child Process my PID is: %d.\n", getpid());
//     }
//     return(0);
// }

// Understanding waitpid()
int main()
{
    int pid1 = fork();
    if (pid1 == -1)
    {
        printf("Error creating process.\n");
        return(1);
    }
    if (pid1 == 0)
    {
        sleep(4);
        printf("Finished execution (%d).\n", getpid());
        return(0);
    }
    int pid2 = fork();
    if (pid2 == -1)
    {
        printf("Error creating a process");
        return(2);
    }
    if (pid2 == 0)
    {
        sleep(1);
        printf("Finished Execution (%d).\n", getpid());
        return(0);
    }

    int pid1_res = waitpid(pid1, NULL, 0);
    printf("Waited for %d.\n", pid1_res);
    int pid2_res = waitpid(pid2, NULL, 0);
    printf("Waited for %d.\n", pid2_res);
    return(0);
}
