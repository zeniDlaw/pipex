/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichettri <ichettri@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:32:50 by ichettri          #+#    #+#             */
/*   Updated: 2024/06/27 18:53:05 by ichettri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_file_des *fds, int *pipefd, char *cmd, char **envp)
{
	if (dup2(fds->infile, STDIN_FILENO) == -1)
		error_exit("dup2 infile.");
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		error_exit("dup2 pipefd[1].");
	close(pipefd[0]);
	close(pipefd[1]);
	close(fds->infile);
	close(fds->outfile);
	execute_cmd(cmd, envp);
}

void	second_child(t_file_des *fds, int *pipefd, char *cmd, char **envp)
{
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		error_exit("dup2 pipefd[0]");
	if (dup2(fds->outfile, STDOUT_FILENO) == -1)
		error_exit("dup2 outfile");
	close(pipefd[0]);
	close(pipefd[1]);
	close(fds->infile);
	close(fds->outfile);
	execute_cmd(cmd, envp);
}

pid_t	create_stchild(t_file_des *fds, int *pipefd, char *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_exit("fork");
	else if (pid == 0)
		first_child(fds, pipefd, cmd, envp);
	return (pid);
}

pid_t	create_ndchild(t_file_des *fds, int *pipefd, char *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_exit("fork");
	else if (pid == 0)
		second_child(fds, pipefd, cmd, envp);
	return (pid);
}

void	handle_parent(t_file_des fds, int *pipefd, pid_t pid1, pid_t pid2)
{
	close(pipefd[0]);
	close(pipefd[1]);
	close(fds.infile);
	close(fds.outfile);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
