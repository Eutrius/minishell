#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[0]))
			return (0);
		if (str[i] == '_' || str[i] == '=')
		{
			i++;
			continue ;
		}
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

int	strs_count(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

int	var_exists(char **env, char *to_check)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], to_check, ft_strlen(to_check)))
			return (1);
		i++;
	}
	return (0);
}

void	free_previous_sorted_exp(char **exported_dup, int i)
{
	while (i)
	{
		free(exported_dup[i]);
		i--;
	}
	free(exported_dup);
}
