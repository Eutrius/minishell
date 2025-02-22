#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static void	handle_sign(char *str, int *i, int *sign);

#include <limits.h>

int	ft_atoll(char *str, long long *result)
{
	long long	num;
	int			sign;
	int			i;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	handle_sign(str, &i, &sign);
	if (!str[i] || (str[i] < '0' || str[i] > '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (num > (LLONG_MAX - (str[i] - '0')) / 10)
			return (0);
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	*result = num * sign;
	return (1);
}

static void	handle_sign(char *str, int *i, int *sign)
{
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}

void	print_string_array(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		printf("%s\n", strs[i]);
		i++;
	}
}

int	is_str_numeric(char *str)
{
	while (*str)
	{
		if (str[0] == '-' || str[0] == '+')
			str++;
		if (ft_isdigit(*str))
			str++;
		else
			break ;
	}
	if (!(*str))
		return (1);
	return (0);
}

int	count_tokens(t_token **token)
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
