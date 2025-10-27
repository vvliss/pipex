/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:00:51 by wilisson          #+#    #+#             */
/*   Updated: 2025/10/27 17:31:20 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int open_files(t_pipex *pipex, char *infile, char *outfile)
{
    pipex->fd_in = open(infile, O_RDONLY); //3
    if(pipex->fd_in == -1)
    {
        perror("Error: infile");
        return(-1);
    }
    pipex->fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644); //4
    if(pipex->fd_out == -1)
    {
        close(pipex->fd_in);
        perror("Error: outfile");
        return(-1);
    }
    return(0);
}

pid_t child_pid(void)
{
    pid_t pid;
    
    pid = fork();
    if(pid == -1)
    {
        perror("Fork fail");
        return(-1);
    }
    else
        return(pid);
}