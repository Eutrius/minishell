/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:34:18 by lonulli           #+#    #+#             */
/*   Updated: 2025/03/07 22:34:18 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	export_no_args(t_data *data);
static void	sort_export(char **sorted_exp);
static void	export_with_args(t_data *data, char **args, int not_valid);
static void	append_vars(t_data *data, char **new_env, int i);

void	custom_export(t_data *data, char **args)
{
	size_t		i;
	int			not_valid;
	extern char	**environ;

	i = 1;
	not_valid = 0;
	if (ft_strslen(args) >= 2)
	{
		while (i < ft_strslen(args))
		{
			if (is_valid_identifier(args[i]) == 0)
			{
				g_status = 255;
				print_error3("bash: ", "export: ", args[i],
					" not a valid identifier");
				not_valid++;
			}
			i++;
		}
		export_with_args(data, args, not_valid);
	}
	if (ft_strslen(args) == 1)
		export_no_args(data);
	environ = data->env;
}

static void	export_with_args(t_data *data, char **args, int not_valid)
{
	int		tokens_count;
	int		i;
	char	**new_env;
	char	**old_env;

	tokens_count = ft_strslen(args) - 1 - not_valid;
	if (tokens_count <= 0)
		return ;
	i = 0;
	new_env = ft_calloc(ft_strslen(data->env) + tokens_count + 1,
			sizeof(char *));
	if (!new_env)
	{
		print_error(ERR_MALLOC, 1);
		return ;
	}
	copy_env(data, new_env, &i);
	old_env = data->env;
	data->env = new_env;
	append_vars(data, args, i);
	sort_export(new_env);
	g_status = 0;
	free(old_env);
}

static void	export_no_args(t_data *data)
{
	int		i;
	char	*equal_sign;

	i = 0;
	sort_export(data->env);
	while (data->env[i])
	{
		equal_sign = ft_strchr(data->env[i], '=');
		if (equal_sign)
		{
			write(1, "declare -x ", 11);
			write(1, data->env[i], equal_sign - data->env[i] + 1);
			write(1, "\"", 1);
			write(1, equal_sign + 1, ft_strlen(equal_sign + 1));
			write(1, "\"", 1);
			write(1, "\n", 1);
		}
		else
			printf("declare -x %s\n", data->env[i]);
		i++;
	}
	g_status = 0;
}

static void	append_vars(t_data *data, char **args, int i)
{
	int		j;
	char	*current_token;
	int		to_sub;

	j = 1;
	while (args[j] != NULL)
	{
		current_token = args[j];
		if (is_valid_identifier(current_token))
		{
			to_sub = replace_or_append(data, current_token, &i);
			if (data->env[to_sub] == NULL)
			{
				print_error(ERR_MALLOC, 1);
				return ;
			}
		}
		j++;
	}
}

static void	sort_export(char **sorted_exp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (sorted_exp[i])
	{
		j = i + 1;
		while (sorted_exp[j])
		{
			if (ft_strcmp(sorted_exp[i], sorted_exp[j]) > 0)
			{
				tmp = sorted_exp[i];
				sorted_exp[i] = sorted_exp[j];
				sorted_exp[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
