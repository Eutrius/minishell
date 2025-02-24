#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

int	is_valid(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

int	calculate_var_len(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$')
		i++;
	while (str[i])
	{
		if (is_valid(str[i]))
			i++;
		else
			break ;
	}
	return (i);
}
