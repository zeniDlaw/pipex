/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichettri <ichettri@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:30:00 by ichettri          #+#    #+#             */
/*   Updated: 2024/06/27 20:00:49 by ichettri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_file_des
{
	int	infile;
	int	outfile;
}		t_file_des;

void	first_child(t_file_des *fds, int *pipefd, char *cmd, char **envp);
void	second_child(t_file_des *fds, int *pipefd, char *cmd, char **envp);
pid_t	create_stchild(t_file_des *fds, int *pipefd, char *cmd, char **envp);
pid_t	create_ndchild(t_file_des *fds, int *pipefd, char *cmd, char **envp);
void	handle_parent(t_file_des fds, int *pipefd, pid_t pid1, pid_t pid2);
void	error_exit(const char *message);
void	execute_cmd(char *cmd, char **envp);
void	ft_free_tab(char **tab);

#endif
