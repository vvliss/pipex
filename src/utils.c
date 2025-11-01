/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:00:51 by wilisson          #+#    #+#             */
/*   Updated: 2025/11/01 17:47:27 by wilisson         ###   ########.fr       */
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

pid_t safe_fork(void)
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

char **split_cmd(char *cmd)
{
    char **arr;
    if(cmd)
    {
        arr = ft_split(cmd, ' ');
        if(!arr)
            return(NULL);
        else
            return(arr);  
    }
    else
        return(NULL);
}

void close_fds(int fd1, int fd2, int fd3, int fd4)
{
    if(fd1 >= 0)
        close(fd1);
    if(fd2 >= 0)
        close(fd2);
    if(fd3 >= 0)
        close(fd3);
    if(fd4 >= 0)
        close(fd4);
}

void free_arr(char **arr)
{
    int i = 0;
    if(!arr)
        return;
    while(arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}
