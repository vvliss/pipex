/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:16:51 by wilisson          #+#    #+#             */
/*   Updated: 2025/11/01 17:24:46 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_exit(char *msg)
{
    ft_putstr_fd("Error", 2);
    ft_putstr_fd("\n", 2);
    exit(1);
}

void error_exit_prefix(char *prefix, char *msg)
{
    
}

void perror_exit(char *msg)
{
    
}

void error_cmd_not_found(char *cmd)
{
    
}

void error_exit_code(char *msg, int exit_code)
{
    
}
