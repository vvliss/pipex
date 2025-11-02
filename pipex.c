/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:12:10 by wilisson          #+#    #+#             */
/*   Updated: 2025/11/02 21:31:51 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	first_child(t_pipex *pipex)
{
	close(pipex->pipe_fd[0]);
	if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
	{
		close(pipex->fd_in);
		close(pipex->pipe_fd[1]);
		exit(1);
	}
	close(pipex->fd_in);
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		close(pipex->pipe_fd[1]);
		exit(1);
	}
	close(pipex->pipe_fd[1]);
	execute_cmd(pipex->cmd1, pipex->envp);
	exit(1);
}

static void	second_child(t_pipex *pipex)
{
	close(pipex->pipe_fd[1]);
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
	{
		close(pipex->pipe_fd[0]);
		close(pipex->fd_out);
		exit(1);
	}
	close(pipex->pipe_fd[0]);
	if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
	{
		close(pipex->fd_out);
		exit(1);
	}
	close(pipex->fd_out);
	execute_cmd(pipex->cmd2, pipex->envp);
	exit(1);
}

static int	init_pipex(t_pipex *pipex, int ac, char **av, char **envp)
{
	if (ac != 5)
	{
		error_exit("Usage: ./pipex infile cmd1 cmd2 outfile", 1);
		return (0);
	}
	ft_memset(pipex, 0, sizeof(t_pipex));
	pipex->cmd1 = av[2];
	pipex->cmd2 = av[3];
	pipex->envp = envp;
	return (1);
}

static int	setup_files_and_pipe(t_pipex *pipex, char *infile, char *outfile)
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

static void	cleanup_pipex(t_pipex *pipex)
{
	close_fds(pipex->fd_in, pipex->fd_out, pipex->pipe_fd[0], pipex->pipe_fd[1]);
}

static int	validate_commands(t_pipex *pipex)
{
	if (!pipex->cmd1 || !*pipex->cmd1)
	{
		ft_putstr_fd("pipex: command not found: \n", 2);
		return (0);
	}
	if (!pipex->cmd2 || !*pipex->cmd2)
	{
		ft_putstr_fd("pipex: command not found: \n", 2);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		exit_code;

	if (!init_pipex(&pipex, ac, av, envp) || !setup_files_and_pipe(&pipex, av[1], av[4]))
		return (1);
	if (!validate_commands(&pipex))
		return(127);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		return (cleanup_pipex(&pipex), 1);
	if (pipex.pid1 == 0)
		first_child(&pipex);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		return (cleanup_pipex(&pipex), 1);
	if (pipex.pid2 == 0)
		second_child(&pipex);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, &pipex.status, 0);
	exit_code = WEXITSTATUS(pipex.status);
	cleanup_pipex(&pipex);
	return (exit_code);
}
