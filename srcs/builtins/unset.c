/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:34:29 by lonulli           #+#    #+#             */
/*   Updated: 2025/03/07 22:34:29 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	unset_variable(t_data *data, char **new_env, char **to_remove);
static int	is_variable_to_unset(char *env_var, char **to_remove);
static char	**reallocate_env(t_data *data, char **to_remove);
static char	**fill_to_remove(char **args);

void	custom_unset(t_data *data, char **args)
{
	char		**new_env;
	char		**to_remove;
	extern char	**environ;

	g_status = 0;
	if (!args[1])
		return ;
	to_remove = fill_to_remove(args);
	if (!to_remove)
		return ;
	new_env = reallocate_env(data, to_remove);
	if (new_env == NULL)
	{
		print_error(ERR_MALLOC);
		ft_free_strs(to_remove);
		return ;
	}
	unset_variable(data, new_env, to_remove);
	data->env = new_env;
	environ = new_env;
}

static char	**reallocate_env(t_data *data, char **to_remove)
{
	char	**new_env;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (data->env[i])
	{
		if (!is_variable_to_unset(data->env[i], to_remove))
			count++;
		i++;
	}
	new_env = ft_calloc(count + 1, sizeof(char *));
	if (new_env == NULL)
	{
		print_error(ERR_MALLOC);
		return (NULL);
	}
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
	if (to_remove == NULL)
	{
		print_error(ERR_MALLOC);
		return (NULL);
	}
	while (args[i])
	{
		to_remove[j] = ft_strdup(args[i]);
		if (to_remove[j] == NULL)
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
	int		i;
	int		j;
	char	**old_env;

	i = 0;
	j = 0;
	old_env = data->env;
	while (old_env[i])
	{
		if (is_variable_to_unset(old_env[i], to_remove))
			free(old_env[i]);
		else
			new_env[j++] = old_env[i];
		i++;
	}
	free(old_env);
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
