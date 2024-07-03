/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichettri <ichettri@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:32:51 by ichettri          #+#    #+#             */
/*   Updated: 2024/07/02 13:45:46 by ichettri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		**pipes;
	int		cmd_no;
	char	**cmds;
	char	**envp;
	pid_t	*pids;
}			t_pipex;

void		error_exit(const char *message);
void		execute_cmd(char *cmd, char **envp);
void		ft_free_tab(char **tab);
void		close_pipenfile(t_pipex *pipex);
void		check_args(int argc);

#endif
