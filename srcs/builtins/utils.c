#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static void	handle_sign(char *str, int *i, int *sign);

#include <limits.h>

int	check_exit_value(char *str)
{
	long long	num;
	int			sign;
	int			i;

	if (!ft_strcmp(str, "--"))
		return (1);
	num = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	handle_sign(str, &i, &sign);
	if (!str[i] || (str[i] < '0' || str[i] > '9'))
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		if (num > (LLONG_MAX - (str[i] - '0')) / 10)
			return (0);
		num = (num * 10) + (str[i] - '0');
		i++;
	}
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

int	count_tokens(t_token **token)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	return (i);
}

int	is_builtin(char *buf, t_data *data)
{
	if (!ft_strcmp(buf, "echo"))
		custom_echo(data);
	if (!ft_strcmp(buf, "cd"))
		custom_chdir(data);
	if (!ft_strcmp(buf, "pwd"))
		custom_pwd();
	if (!ft_strcmp(buf, "export"))
		custom_export(data);
	if (!ft_strcmp(buf, "unset"))
		custom_unset(data);
	if (!ft_strcmp(buf, "env"))
		custom_env(data);
	if (!ft_strcmp(buf, "exit"))
		clean_exit(data);
	return (0);
}
