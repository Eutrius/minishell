#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static void	unset_variable(t_data *data, char **new_env);
static char	**reallocate_env(t_data *data);

void	custom_unset(t_data *data)
{
	char	**new_env;

	if (!ft_strcmp("unset", data->cmd_line[0]->content))
	{
		if (!data->cmd_line[1])
			return ;
		new_env = reallocate_env(data);
		if (!new_env)
			return ;
		unset_variable(data, new_env);
		free(data->env);
		data->env = new_env;
	}
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

static void	unset_variable(t_data *data, char **new_env)
{
	int		i;
	int		j;
	char	*to_remove;
	int		are_equals;

	are_equals = 0;
	to_remove = data->cmd_line[1]->content;
	i = 0;
	j = 0;
	while (data->env[i])
	{
		are_equals = ft_strncmp(to_remove, data->env[i], ft_strlen(to_remove));
		if (!are_equals && data->env[i][ft_strlen(to_remove)] == '=')
			free(data->env[i]);
		else
			new_env[j++] = data->env[i];
		i++;
	}
	new_env[i] = NULL;
}
