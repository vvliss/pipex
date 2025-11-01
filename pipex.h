/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:29:26 by wilisson          #+#    #+#             */
/*   Updated: 2025/11/01 19:37:44 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <../libft/libft.h>

typedef struct s_pipex {
int         fd_out;
int         fd_in;
int         pipe_fd[2];
pid_t       pid1;
pid_t       pid2;
char        **envp;
char        *cmd1;
char        *cmd2;
int         status
}     t_pipex;

int open_files(t_pipex *pipex, char *infile, char *outfile);

#endif