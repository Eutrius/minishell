#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		
		if (!ft_isalpha(str[0]))
			return (0);
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	value_checker(char **sorted_exp, int i)
{
	char	*tmp;

	if (ft_strchr(sorted_exp[i], '=') && sorted_exp[i][find_eq_i(sorted_exp[i])
		+ 1] == '\0')
	{
		tmp = sorted_exp[i];
		sorted_exp[i] = ft_strjoin(sorted_exp[i], "\"\"");
		free(tmp);
	}
}

int	find_eq_i(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int iterate_vars(t_data *data, char **args, int i, int token_count)
{
	int  j;
	char *current_token;
	int  to_sub;

	j = 1;
	while (token_count)
	{
		current_token = args[j];
		to_sub = check_var_existence(data->env, current_token);
		// if (to_sub < 0)
		// 	to_sub = i;
		// if (to_sub == i || check_equal(current_token))
		// 	data->env[to_sub] = current_token;
		if (to_sub >= 0)
		{
			if (check_equal(current_token))
				data->env[to_sub] = current_token;
		}
		else
			data->env[i] = current_token;
		i++;
		token_count--;
	}
	return 1;
}

char	*strdup_and_add_quotes(char *str)
{
	int		len;
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	len = ft_strlen(str) + 3;
	new = ft_calloc(len, 1);
	if (!new)
	{
		print_error(ERR_MALLOC);
		return (NULL);
	}
	while (str[j] && str[j] != '=')
		new[i++] = str[j++];
	if (str[j++] == '=')
		new[i++] = '=';
	else
	{
		new[i] = '\0';
		return (new);
	}
	new[i++] = '"';
	while (str[j])
		new[i++] = str[j++];
	new[i++] = '"';
	new[i] = '\0';
	return (new);
}

char	**export_strsdup(char **strs)
{
	int		i;
	int		quantity;
	char	**new_env;

	i = 0;
	quantity = ft_strslen(strs);
	new_env = ft_calloc(quantity + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	while (strs[i])
	{
		new_env[i] = strdup_and_add_quotes(strs[i]);
		if (!new_env[i])
		{
			ft_free_strs(strs);
			print_error(ERR_MALLOC);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	check_equal(char *ptr)
{
	int	has_equals;
	int	k;

	has_equals = 0;
	k = 0;
	while (ptr[k] && ptr[k] != '=')
		k++;
	if (ptr[k] == '=')
		has_equals = 1;
	return (has_equals);
}

int	check_var_existence(char **env, char *ptr)
{
	int	i;
	int	equal_index;
	int j;

	i = 0;
	while (ptr[i] && ptr[i] != '=')
		i++;
	equal_index = i;
	i = 0;
	while (env[i])
	{
		j = 0;
		while(env[i][j] && env[i][j] != '=')
			j++;
		if (!ft_strncmp(env[i], ptr, ft_maxint(j,equal_index)))
			return (i);
		i++;
	}
	return (-1);
}
