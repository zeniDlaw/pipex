/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichettri <ichettri@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:47:46 by ichettri          #+#    #+#             */
/*   Updated: 2024/07/02 13:45:16 by ichettri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	close_pipenfile(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_no - 1)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		free(pipex->pipes[i]);
		i++;
	}
	free(pipex->pipes);
	close(pipex->infile);
	close(pipex->outfile);
}

void	check_args(int argc)
{
	if (argc < 5)
		error_exit("Usuage: ./pipex infile cmd1 cmd2 cmd3 ... cmdn outfile.\n");
}
