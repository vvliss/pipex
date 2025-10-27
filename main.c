/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:12:10 by wilisson          #+#    #+#             */
/*   Updated: 2025/10/27 18:51:31 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void first_child(t_pipex *pipex)
{
    if(pipex->pipe_fd[0])
        close(pipex->pipe_fd[0]);
    dup2(pipex->fd_in, STDIN_FILENO);
    if(dup2(pipex->fd_in, STDIN_FILENO) == -1)
    {
        perror("dup2 stdin failed");
        exit(EXIT_FAILURE);
    }
    close(pipex->fd_in);
    dup2(pipex->pipe_fd[1], STDOUT_FILENO);
    if(dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
    {
        perror("dup2 failed");
        exit(EXIT_FAILURE);
    }
    close(pipex->pipe_fd[1]);
    execve();
}

int main(t_pipex *pipex, int ac, char **av, char **envp)
{
    int fd_inp;
    int fd_out;
    
    if(ac != 5)
    {
        write(2, "Invalid number of arguments\n", 28);
        return(1);
    }
    if(open_files(av[1], av[4], &fd_inp, &fd_out) == -1)
        return(1); 
    if(pipe(pipex->pipe_fd) == -1)
    {
        perror("pipe fail");
        close(fd_inp);
        close(fd_out);
        return(1);
    }
    
}