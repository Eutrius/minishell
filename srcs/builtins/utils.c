#include "libft.h"
#include "minishell.h"
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

static void	handle_sign(char *str, int *i, int *sign);
int			overflow_check(int sign, long long num, char *str, int i);

int	check_exit_value(char *str)
{
	long long	num;
	int			sign;
	int			i;

	if (!str)
		return (0);
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
		if (!overflow_check(sign, num, str, i))
			return (0);
		num = (num * 10) + (str[i++] - '0');
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

int	overflow_check(int sign, long long num, char *str, int i)
{
	if (sign == 1 && num > (LLONG_MAX - (str[i] - '0')) / 10)
		return (0);
	else if (sign == -1)
	{
		if (num > LLONG_MAX / 10)
			return (0);
		if (num == LLONG_MAX / 10 && (str[i] - '0') > 7)
			return (0);
	}
	return (1);
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
