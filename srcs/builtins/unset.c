#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	unset_variable(t_data *data, char **new_env, char **to_remove);
static int	is_variable_to_unset(char *env_var, char **to_remove);
static char	**reallocate_env(t_data *data);
static char	**fill_to_remove(char **args);

void	custom_unset(t_data *data, char **args)
{
	char	**new_env;
	char	**to_remove;

	if (!args[1])
		return ;
	to_remove = fill_to_remove(args);
	new_env = reallocate_env(data);
	if (!new_env)
		return ;
	unset_variable(data, new_env, to_remove);
	data->env = new_env;
}

static char	**reallocate_env(t_data *data)
{
	char	**new_env;
	int		i;

	i = 0;
	while (data->env[i])
		i++;
	new_env = ft_calloc(i + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	return (new_env);
}

static char	**fill_to_remove(char **args)
{
	int		i;
	char	**to_remove;
	int		j;

	i = 1;
	j = 0;
	to_remove = ft_calloc((ft_strslen(args)), sizeof(char *));
	if (!to_remove)
		return (NULL);
	while (args[i])
	{
		to_remove[j] = ft_strdup(args[i]);
		if (!to_remove[j])
		{
			to_remove[j] = NULL;
			ft_free_strs(to_remove);
			return (NULL);
		}
		j++;
		i++;
	}
	return (to_remove);
}

static void	unset_variable(t_data *data, char **new_env, char **to_remove)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->env[i])
	{
		if (is_variable_to_unset(data->env[i], to_remove))
			free(data->env[i]);
		else
			new_env[j++] = data->env[i];
		i++;
	}
	ft_free_strs(to_remove);
}

static int	is_variable_to_unset(char *env_var, char **to_remove)
{
	int		k;
	size_t	var_len;
	char	*equals_pos;

	k = 0;
	equals_pos = ft_strchr(env_var, '=');
	if (equals_pos)
		var_len = equals_pos - env_var;
	else
		var_len = ft_strlen(env_var);
	while (to_remove[k])
	{
		if (ft_strlen(to_remove[k]) == var_len && ft_strncmp(env_var,
				to_remove[k], var_len) == 0)
			return (1);
		k++;
	}
	return (0);
}
