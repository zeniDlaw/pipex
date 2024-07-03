/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichettri <ichettri@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:56:42 by ichettri          #+#    #+#             */
/*   Updated: 2024/07/02 20:15:12 by ichettri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/libftprintf.h"
#include "pipex_bonus.h"

void	init_fds(t_pipex *pipex, char **argv, int argc)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
	{
		ft_printf("pipex: %s: No such file or directory.\n", argv[1]);
		exit(0);
	}
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile < 0)
	{
		ft_printf("pipex: failed to open %s for writing.\n", argv[argc - 1]);
		exit(0);
	}
}

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int	i;

	i = 0;
	pipex->cmd_no = argc - 3;
	pipex->cmds = &argv[2];
	pipex->envp = envp;
	init_fds(pipex, argv, argc);
	pipex->pipes = malloc(sizeof(int *) * (pipex->cmd_no - 1));
	if (!(pipex->pipes))
		return ;
	while (i < pipex->cmd_no - 1)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipex->pipes[i]) == -1)
			error_exit("pipes");
		i++;
	}
	pipex->pids = malloc(sizeof(pid_t) * pipex->cmd_no);
	if (!(pipex->pids))
		return ;
}

void	last_childnexe(t_pipex *pipex, int index)
{
	int	i;

	i = 0;
	if (index == pipex->cmd_no - 1)
	{
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			error_exit("dup2 outfile");
	}
	else
	{
		if (dup2(pipex->pipes[index][1], STDOUT_FILENO) == -1)
			error_exit("dup2 pipe write");
	}
	while (i < pipex->cmd_no - 1)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
	close(pipex->infile);
	close(pipex->outfile);
	execute_cmd(pipex->cmds[index], pipex->envp);
}

void	child_process(t_pipex *pipex, int index)
{
	if (index == 0)
	{
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			error_exit("dup2 infile");
	}
	else
	{
		if (dup2(pipex->pipes[index - 1][0], STDIN_FILENO) == -1)
			error_exit("dup2 pipe read");
	}
	last_childnexe(pipex, index);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;
	int		k;

	check_args(argc);
	init_pipex(&pipex, argc, argv, envp);
	i = 0;
	k = 0;
	while (i < pipex.cmd_no)
	{
		pipex.pids[i] = fork();
		if (pipex.pids[i] < 0)
			error_exit("fork");
		else if (pipex.pids[i] == 0)
			child_process(&pipex, i);
		i++;
	}
	close_pipenfile(&pipex);
	while (k < pipex.cmd_no)
	{
		waitpid(pipex.pids[i], NULL, 0);
		k++;
	}
	free(pipex.pids);
}
