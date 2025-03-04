#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void		free_paths(char **path, char *error);
int			is_path_given(char *full_path);

static char	**get_paths(char **env)
{
	char	**path;

	while (!ft_strnstr((*env), "PATH=", 5))
		env++;
	path = ft_split(*env + 5, ':');
	return (path);
}

char	*pathfinder(const char *cmd, char **env)
{
	char	**path;
	int		i;
	char	*return_path;
	size_t	len;

	return_path = NULL;
	i = 0;
	path = get_paths(env);
	while (path && path[i])
	{
		len = ft_strlen((char *)cmd) + ft_strlen(path[i]) + 2;
		return_path = ft_calloc(sizeof(char), (len));
		if (!return_path)
			free_paths(path, "ERROR");
		ft_strlcat(return_path, path[i], len);
		return_path[ft_strlen(path[i++])] = '/';
		ft_strlcat(return_path, cmd, len);
		if (access(return_path, F_OK | X_OK) == 0)
			break ;
		free(return_path);
	}
	if (path && !path[i])
		return_path = NULL;
	// free_paths(path, "NO_ERROR");
	return (return_path);
}

/*Function to check if command is given as full path*/

int	is_path_given(char *full_path)
{
	struct stat	buf;

	if (stat(full_path, &buf) == 0)
	{
		if (!S_ISREG(buf.st_mode) || S_ISDIR(buf.st_mode))
			return (0);
	}
	if (access(full_path, F_OK | X_OK) == 0)
		return (1);
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
