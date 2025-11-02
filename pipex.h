/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:29:26 by wilisson          #+#    #+#             */
/*   Updated: 2025/11/02 20:12:50 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <sys/stat.h>

typedef struct s_pipex {
	int         fd_out;
	int         fd_in;
	int         pipe_fd[2];
	pid_t       pid1;
	pid_t       pid2;
	char        **envp;
	char        *cmd1;
	char        *cmd2;
	int         status;
	int			first_status;
}				t_pipex;

int		open_files(t_pipex *pipex, char *infile, char *outfile);
pid_t	safe_fork(void);
char	**split_cmd(char *cmd);
void	close_fds(int fd1, int fd2, int fd3, int fd4);
void	free_arr(char **arr);
char	*get_cmd_path(char *cmd, char **envp);
void    execute_cmd(char *cmd, char **envp);
void	error_exit(char *msg, int exit_code);
void	perror_exit(char *msg);
void	print_error(char *prefix, char *message);
void	print_file_error(char *filename);

#endif