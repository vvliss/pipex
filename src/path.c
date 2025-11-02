/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:59:52 by wilisson          #+#    #+#             */
/*   Updated: 2025/11/02 21:29:50 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char *search_in_dirs(char *cmd, char **path_dirs)
{
    int i;
    char *full_path;
    char *tmp;

    i = 0;
    while(path_dirs[i])
    {
        tmp = ft_strjoin(path_dirs[i], "/");
        full_path = ft_strjoin(tmp, cmd);
        free(tmp);
        if(access(full_path, X_OK) == 0)
            return(full_path);
        free(full_path);
        i++;
    }
    return(NULL);
}

char *find_path(char *cmd, char **envp)
{
    char *path_env;
    char **path_dirs;
    char *found_path;
    int found_env;
    int i;
    
    found_env = 0;
    i = 0;
    while(envp[i] && !found_env)
    {
        if(ft_strncmp(envp[i], "PATH=", 5) == 0)
        {
            path_env = envp[i] + 5;
            found_env = 1;
        }
        i++;
    }
    if (!found_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	found_path = search_in_dirs(cmd, path_dirs);
	free_arr(path_dirs);
	return (found_path);
}

static int is_absolute_path(char *cmd)
{
    if(cmd[0] == '/')
        return(1);
    return(0);
}

char *get_cmd_path(char *cmd, char **envp)
{
    if(is_absolute_path(cmd))
    {
        if(access(cmd, X_OK) == 0)
            return(ft_strdup(cmd));
        return(NULL);
    }
    else if (ft_strchr(cmd, '/'))
    {
        if(access(cmd, X_OK) == 0)
            return(ft_strdup(cmd));
        return(NULL);
    }
    else    
        return(find_path(cmd, envp));
}

void execute_cmd(char *cmd, char **envp)
{
    char *path;
    char **args;
    
    args = split_cmd(cmd);
    if(!args)
        exit(1);
    path = get_cmd_path(args[0], envp);
    if(!path)
    {
        free_arr(args);
        exit(127);
    }
    execve(path, args, envp);
    free(path);
    free_arr(args);
    exit(1);
}
