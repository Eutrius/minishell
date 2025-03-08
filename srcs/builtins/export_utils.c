/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:34:15 by lonulli           #+#    #+#             */
/*   Updated: 2025/03/07 22:34:16 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str[i] || (ft_isalpha(str[0]) == 0 && str[0] != '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	value_checker(char **sorted_exp, int i)
{
	char	*tmp;
	int		eq_index;

	eq_index = 0;
	while (sorted_exp[i][eq_index] && sorted_exp[i][eq_index] != '=')
		eq_index++;
	if (sorted_exp[i][eq_index] == '=' && sorted_exp[i][eq_index + 1] == '\0')
	{
		tmp = sorted_exp[i];
		sorted_exp[i] = ft_strjoin(sorted_exp[i], "\"\"");
		if (sorted_exp[i] == NULL)
		{
			free(tmp);
			print_error(ERR_MALLOC, 1);
			return ;
		}
		free(tmp);
	}
}

int	check_var_existence(char **env, char *ptr)
{
	int	i;
	int	equal_index;
	int	j;

	i = 0;
	while (ptr[i] && ptr[i] != '=')
		i++;
	equal_index = i;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		if (!ft_strncmp(env[i], ptr, ft_maxint(j, equal_index)))
			return (i);
		i++;
	}
	return (-1);
}

int	replace_or_append(t_data *data, char *current_token, int *i)
{
	int	to_sub;

	to_sub = check_var_existence(data->env, current_token);
	if (to_sub < 0)
	{
		to_sub = *i;
		data->env[to_sub] = ft_strdup(current_token);
		(*i)++;
	}
	else if (check_equal(current_token))
	{
		free(data->env[to_sub]);
		data->env[to_sub] = ft_strdup(current_token);
	}
	return (to_sub);
}

void	copy_env(t_data *data, char **new_env, int *i)
{
	while (data->env && data->env[*i])
	{
		new_env[*i] = data->env[*i];
		(*i)++;
	}
}
