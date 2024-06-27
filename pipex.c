/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichettri <ichettri@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:14:36 by ichettri          #+#    #+#             */
/*   Updated: 2024/06/27 18:26:20 by ichettri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf/libftprintf.h"
#include "pipex.h"
#include <fcntl.h>

void	init_fds(t_file_des *fds, char *infile, char *outfile)
{
	fds->infile = open(infile, O_RDONLY);
	if (fds->infile < 0)
	{
		ft_printf(" pipex: %s: No such file or directory.\n", infile);
		exit(0);
	}
	fds->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds->outfile < 0)
	{
		ft_printf(" pipex: failed to open %s for writing.\n", outfile);
		exit(0);
	}
}

void	check_args(int argc)
{
	if (argc != 5)
		error_exit("Usuage: ./pipex infile cmd1 cmd2 outfile.\n");
}

void	create_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
		error_exit("pipe");
}

int	main(int argc, char **argv, char **envp)
{
	t_file_des	fds;
	int			pipefd[2];
	pid_t		pid1;
	pid_t		pid2;

	check_args(argc);
	init_fds(&fds, argv[1], argv[4]);
	create_pipe(pipefd);
	pid1 = create_stchild(&fds, pipefd, argv[2], envp);
	pid2 = create_ndchild(&fds, pipefd, argv[3], envp);
	handle_parent(fds, pipefd, pid1, pid2);
	return (0);
}
