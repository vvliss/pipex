/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:16:51 by wilisson          #+#    #+#             */
/*   Updated: 2025/11/02 20:12:39 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *msg, int exit_code)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(exit_code);
}

void	perror_exit(char *msg)
{
	perror(msg);
	exit(1);
}

void	print_file_error(char *filename)
{
	ft_putstr_fd("pipex: ", 2);
	perror(filename);
}

void	print_error(char *prefix, char *message)
{
	ft_putstr_fd("pipex: ", 2);
	if (prefix)
	{
		ft_putstr_fd(prefix, 2);
		ft_putstr_fd(": ", 2);
	}
	if (message)
		ft_putstr_fd(message, 2);
	else
		perror("");
}