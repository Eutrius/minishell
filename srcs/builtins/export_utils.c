#include "libft.h"
#include "minishell.h"
#include <stdio.h>
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
