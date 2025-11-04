/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:24:00 by wilisson          #+#    #+#             */
/*   Updated: 2025/11/04 19:26:15 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	validate_commands(t_pipex *pipex)
{
	int	valid;

	valid = 1;
	if (!pipex->cmd1 || !*pipex->cmd1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		if (pipex->cmd1)
			ft_putendl_fd(pipex->cmd1, 2);
		else
			ft_putendl_fd("(null)", 2);
		valid = 0;
	}
	if (!pipex->cmd2 || !*pipex->cmd2)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		if (pipex->cmd2)
			ft_putendl_fd(pipex->cmd2, 2);
		else
			ft_putendl_fd("(null)", 2);
		valid = 0;
	}
	return (valid);
}

int	setup_files_and_pipe(t_pipex *pipex, char *infile, char *outfile)
{
	if (open_files(pipex, infile, outfile) == -1)
		return (0);
	if (pipe(pipex->pipe_fd) == -1)
	{
		close_fds(pipex->fd_in, pipex->fd_out, -1, -1);
		return (0);
	}
	return (1);
}

void	close_fds(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
	if (fd3 >= 0)
		close(fd3);
	if (fd4 >= 0)
		close(fd4);
}
