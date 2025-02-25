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
	int	start;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$')
	{
		start = i;
		i++;
		while (is_valid(str[i]))
			i++;
		return (i - start);
	}
	return (0);
}
