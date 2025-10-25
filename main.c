/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:12:10 by wilisson          #+#    #+#             */
/*   Updated: 2025/10/25 19:03:57 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **envp)
{
    int fd_inp;
    int fd_out;
    
    if(ac != 5)
    {
        perror("Invalid input");
        return(0);
    }
    else
    {
        open_files(av[1], av[4], &fd_inp, &fd_out);
        
    }
}