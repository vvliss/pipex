/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:00:51 by wilisson          #+#    #+#             */
/*   Updated: 2025/10/25 18:44:23 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void open_files(char *infile, char *outfile, int *fd_in, int *fd_out)
{
    *fd_in = open(infile, O_RDONLY);
    if(*fd_in == -1)
    {
        perror("Error: infile");
        exit(1);
    }
    *fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(*fd_out == -1)
    {
        close(*fd_in);
        perror("Error: outfile");
        exit(1);
    }
}