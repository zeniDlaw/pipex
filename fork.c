/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichettri <ichettri@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:28:35 by ichettri          #+#    #+#             */
/*   Updated: 2024/06/24 17:53:06 by ichettri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

// int main(void)
// {
//     int id;
//     int n;
//     int i;
//     int stat;

//     id = fork();
//     if (id == 0)
//         n = 1;
//     else
//         n = 6;

//     if (id != 0)
//         wait(&stat);
    
//     i = n;
//     while (i < n + 5)
//     {
//         printf("%d ", i);
//         fflush(stdout);
//         i++;
//     }

//     if (id != 0)
//         printf("\n");
//     // printf("Hello World from process\n");
// //     if (id == 0)
// //         printf("Hello from child process\n");
// //     else
// //         printf("Hello from the main process\n");
//     return(0);
// }

// Calling Fork multipile times.

int main(int argc, char **argv)
{
    int id1;
    int id2;

    id1 = fork();
    id2 = fork();
    if (id1 == 0)
    {
        if (id2 == 0)
            printf("We are process y.\n");
        else
            printf("We are process x.\n");
    }
    else
    {
        if (id2 == 0)
            printf("We are process z.\n");
        else
            printf("We are the parent process!\n"); 
    }
    return(0);
}
