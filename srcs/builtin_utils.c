#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>

int	is_str_numeric(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str))
			str++;
		else
			break ;
	}
	if (!(*str))
		return (1);
	return (0);
}

int	token_count(t_token **token)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	return (i);
}

int	is_builtin(char *buf)
{
	if (!ft_strcmp(buf, "echo"))
		return (1);
	if (!ft_strcmp(buf, "cd"))
		return (1);
	if (!ft_strcmp(buf, "pwd"))
		return (1);
	if (!ft_strcmp(buf, "export"))
		return (1);
	if (!ft_strcmp(buf, "unset"))
		return (1);
	if (!ft_strcmp(buf, "env"))
		return (1);
	if (!ft_strcmp(buf, "exit"))
		return (1);
	return (0);
}
