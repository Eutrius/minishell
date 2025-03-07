/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:33:53 by lonulli           #+#    #+#             */
/*   Updated: 2025/03/07 22:33:54 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void		free_paths(char **path, char *error);
int			is_path_given(char *full_path);
static int	check_absolute_path(const char *cmd);
static char	**get_paths(char **env);

char	*pathfinder(const char *cmd, char **env)
{
	char	**path;
	int		i;
	char	*return_path;
	char	*temp;

	if (check_absolute_path(cmd))
		return (ft_strdup(cmd));
	i = 0;
	path = get_paths(env);
	while (path && path[i])
	{
		temp = ft_strjoin(path[i], "/");
		return_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(return_path, F_OK | X_OK) == 0)
		{
			ft_free_strs(path);
			return (return_path);
		}
		free(return_path);
		i++;
	}
	ft_free_strs(path);
	return (NULL);
}

static char	**get_paths(char **env)
{
	char	**path;

	while (!ft_strnstr((*env), "PATH=", 5))
		env++;
	path = ft_split(*env + 5, ':');
	return (path);
}

static int	check_absolute_path(const char *cmd)
{
	if (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "../",
			3) == 0)
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (1);
	}
	return (0);
}

void	free_paths(char **path, char *error)
{
	int	i;

	i = -1;
	while (path[++i] != NULL && path)
		free(path[i]);
	if (path)
		free(path);
	if (ft_strcmp(error, "ERROR"))
		exit(1);
}
