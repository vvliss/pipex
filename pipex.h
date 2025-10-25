/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:29:26 by wilisson          #+#    #+#             */
/*   Updated: 2025/10/25 18:48:36 by wilisson         ###   ########.fr       */
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

typedef struct s_pipex{
int fdout;
int  fdin;
int    ac;
char **av;
char **envp;
}     t_pipex;

void open_files(char *infile, char *outfile, int *fd_in, int *fd_out);

#endif