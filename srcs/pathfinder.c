#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void		free_paths(char **path, char *error);
int			is_path_given(char *full_path);
static int check_absolute_path(const char *cmd);
static char	**get_paths(char **env);

char	*pathfinder(const char *cmd, char **env)
{
	char	**path;
	int		i;
	char	*return_path;
	size_t	len;

  if (check_absolute_path(cmd))
    return ft_strdup(cmd);
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
	return (return_path);
}

static char	**get_paths(char **env)
{
	char	**path;

	while (!ft_strnstr((*env), "PATH=", 5))
		env++;
	path = ft_split(*env + 5, ':');
	return (path);
}

static int check_absolute_path(const char *cmd)
{
  if (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "../", 3) == 0)
  {
    if (access(cmd, X_OK) == 0)
      return 1;
  }
  return 0;
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
