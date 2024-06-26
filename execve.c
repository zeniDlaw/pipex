/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichettri <ichettri@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:26:16 by ichettri          #+#    #+#             */
/*   Updated: 2024/06/22 13:38:09 by ichettri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;

	if (argc > 1)
	{
		i = 0;
		// char *const args[] = {"ls", NULL}; // the command
		char *const envp[] = {NULL};           // env
		execve("/usr/bin/ls", &argv[1], envp); // execute command at the path
	}
	perror("execve");
	return (1);
}
