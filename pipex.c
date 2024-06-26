/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichettri <ichettri@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:14:36 by ichettri          #+#    #+#             */
/*   Updated: 2024/06/26 16:14:13 by ichettri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "./libft/libft.a"
#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

void error_exit(const char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

void execute_command(char *cmd, char **envp)
{
    char *argv[] = {"/bin/sh", "-c", cmd, NULL};
    execve(argv[0], argv, envp);
    error_exit("execve");
}

void first_child(file_des_t *fds, int *pipefd, char *cmd, char **envp)
{
    if (dup2(fds->infile, STDIN_FILENO) == -1)
        error_exit("dup2 infile.");
    if (dup2(pipefd[1], STDOUT_FILENO) == -1)
        error_exit("dup2 pipefd[1].");
    close(pipefd[0]);
    close(pipefd[1]);
    close(fds->infile);
    close(fds->outfile);
    execute_command(cmd, envp);
}

void second_child(file_des_t *fds, int *pipefd, char *cmd, char **envp)
{
    if (dup2(pipefd[0], STDIN_FILENO) == -1)
        error_exit("dup2 pipefd[0]");
    if (dup2(fds->outfile, STDOUT_FILENO) == -1)
        error_exit("dup2 outfile");
    close(pipefd[0]);
    close(pipefd[1]);
    close(fds->infile);
    close(fds->outfile);
    execute_command(cmd, envp);
}

void handle_parent(file_des_t fds, int *pipefd, pid_t pid1, pid_t pid2)
{
    close(pipefd[0]);
    close(pipefd[1]);
    close(fds.infile);
    close(fds.outfile);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

int main(int argc, char **argv, char **envp)
{
    file_des_t fds;
    int     pipefd[2];
    pid_t   pid1;
    pid_t   pid2;

    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    fds.infile = open(argv[1], O_RDONLY);
    if (fds.infile < 0)
        error_exit("open infile");

    fds.outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fds.outfile < 0)
        error_exit("open outfile");

    if (pipe(pipefd) == -1)
        error_exit("pipe");

    pid1 = fork();
    if (pid1 < 0)
        error_exit("fork");
    else if (pid1 == 0)
        first_child(&fds, pipefd, argv[2], envp);

    pid2 = fork();
    if (pid2 < 0)
        error_exit("fork");
    else if (pid2 == 0)
        second_child(&fds, pipefd, argv[3], envp); // Second child: execute cmd2, input from pipe, output to outfile

    // Parent: close all file descriptors and wait for children
    handle_parent(fds, pipefd, pid1, pid2);
    return 0;
}
