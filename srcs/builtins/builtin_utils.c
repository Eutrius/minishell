#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	sort_and_print_export(char **sorted_exp);

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

int	count_tokens(t_token **token)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	return (i);
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

void	print_export(t_data *data)
{
	char	**sorted_exp;
	int		i;

	i = 0;
	sorted_exp = ft_strsdup(data->env);
	if (!sorted_exp)
		return ;
	while (sorted_exp[i])
	{
		sorted_exp[i] = ft_strjoin("declare -x ", sorted_exp[i]);
		if (!sorted_exp[i])
		{
			free_previous_sorted_exp(sorted_exp, i);
			return ;
		}
		i++;
	}
	sort_and_print_export(sorted_exp);
	i = 0;
	while (sorted_exp[i])
	{
		printf("%s\n", sorted_exp[i]);
		i++;
	}
	// free_previous_sorted_exp(sorted_exp,i);
}

static void	sort_and_print_export(char **sorted_exp)
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
				tmp = ft_calloc(ft_strlen(sorted_exp[i]), 1);
				if (!tmp)
					return ;
				ft_strlcpy(tmp, sorted_exp[i], ft_strlen(sorted_exp[i]));
				sorted_exp[i] = sorted_exp[j];
				sorted_exp[j] = tmp;
			}
			j++;
		}
		i++;
	}
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
