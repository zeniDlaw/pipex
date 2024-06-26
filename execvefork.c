/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execvefork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichettri <ichettri@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:39:54 by ichettri          #+#    #+#             */
/*   Updated: 2024/06/22 16:13:14 by ichettri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void callexecve()
{
    char *const args[] = {"ls", NULL};
    char *const envp[] = {NULL};

    execve("usr/bin/ls", args, envp);
    perror("execve");
        exit(EXIT_FAILURE);
}

// int main(void)
// {
//     __pid_t pid;
//     printf("Hi this is the main process. ID is: %d\n", getpid());
//     pid = fork();
//     if (pid == -1)
//         printf("Error while forking\n");
//     else if (pid == 0)
//     {
//         printf("I am the child. But now a new parent. My ID is: %d --- My child's pID is %d\n",getpid(), pid);
//         callexecve();
//     }
//     else if (pid > 1)
//     {
//         printf("I am the parent. My pID is: %d------My child's pID is: %d\n", getpid(), pid);
//         waitpid(pid, NULL, 0);
//         printf("Got back the control?\n");
//     }
// }

int main(void)
{
    __pid_t pid;
    int pfd[2];

    pipe(pfd);
    pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Fork2 Failed.\n");
        return 1;
    }
    else if (pid == 0)
    {
        close(pfd[0]); //close unused end (the reading end) of the pipe
        dup2(pfd[1], 1); 
        close(pfd[1]); //close it immediately since no longer needed/used.
        write(1, "This is a secret message", 26);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(pfd[1]); //close unused end (the writing end) of the pipe
        dup2(pfd[0], 0);  
        close(pfd[0]); //close it immediately since no longer needed/used.
        char str[26];
        read(0, str, 26);
        printf("Parent received: %s.\n", str);
        wait(NULL);
    }
    return EXIT_SUCCESS;
}
