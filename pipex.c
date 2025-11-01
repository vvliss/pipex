/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:12:10 by wilisson          #+#    #+#             */
/*   Updated: 2025/11/01 20:26:44 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	first_child(t_pipex *pipex)
{
	if (pipex->pipe_fd[0])
		close(pipex->pipe_fd[0]);
	if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
		perror_exit("dup2 stdin failed");
	close(pipex->fd_in);
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
		perror_exit("dup2 stdout failed");
	close(pipex->pipe_fd[1]);
	execute_cmd(pipex, pipex->cmd1, pipex->envp);
}

static void	second_child(t_pipex *pipex)
{
	if (pipex->pipe_fd[1])
		close(pipex->pipe_fd[1]);
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
		perror_exit("dup2 stdin failed");
	close(pipex->pipe_fd[0]);
	if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
		perror_exit("dup2 stdout failed");
	close(pipex->fd_out);
	execute_cmd(pipex, pipex->cmd2, pipex->envp);
}

static void	error_cleanup(t_pipex *pipex, char *msg)
{
	close_fds(pipex->fd_in, pipex->fd_out, pipex->pipe_fd[0], pipex->pipe_fd[1]);
	perror_exit(msg);
}

int main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
		error_exit("Usage: ./pipex infile cmd1 cmd2 outfile", 1);
	init_pipex(&pipex, av, envp);
	if (open_files(&pipex, av[1], av[4]) == -1)
		exit(1);
	if (pipe(pipex.pipe_fd) == -1)
		error_cleanup(&pipex, "pipe");
	create_children(&pipex);
	cleanup_and_wait(&pipex);
	return (0);
}
