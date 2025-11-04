/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:00:51 by wilisson          #+#    #+#             */
/*   Updated: 2025/11/04 19:26:09 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
		return (S_ISDIR(path_stat.st_mode));
	return (0);
}

int	open_files(t_pipex *pipex, char *infile, char *outfile)
{
	if (is_directory(infile))
		return (print_error(infile, "Is a directory"), -1);
	pipex->fd_in = open(infile, O_RDONLY);
	if (pipex->fd_in == -1)
		print_file_error(infile);
	pipex->fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_out == -1)
	{
		if (pipex->fd_in != -1)
			close(pipex->fd_in);
		print_file_error(outfile);
		return (-1);
	}
	return (0);
}

pid_t	safe_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	return (pid);
}

char	**split_cmd(char *cmd)
{
	char	**arr;

	if (cmd)
	{
		arr = ft_split(cmd, ' ');
		if (!arr)
			return (NULL);
		else
			return (arr);
	}
	else
		return (NULL);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
