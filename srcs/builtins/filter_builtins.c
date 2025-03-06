#include "libft.h"
#include "minishell.h"
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

static int	is_builtin1(char **args, t_data *data);
static int	is_builtin2(char **args, t_data *data);

int	is_builtin(char **args, t_data *data)
{
	if (!is_builtin1(args, data) && !is_builtin2(args, data))
		return (0);
	return (1);
}

static int	is_builtin1(char **args, t_data *data)
{
	if (!ft_strcmp(args[0], "echo"))
	{
		custom_echo(args);
		return (1);
	}
	if (!ft_strcmp(args[0], "cd"))
	{
		custom_chdir(args);
		return (1);
	}
	if (!ft_strcmp(args[0], "pwd"))
	{
		custom_pwd();
		return (1);
	}
	if (!ft_strcmp(args[0], "export"))
	{
		custom_export(data, args);
		return (1);
	}
	return (0);
}

static int	is_builtin2(char **args, t_data *data)
{
	if (!ft_strcmp(args[0], "export"))
	{
		custom_export(data, args);
		return (1);
	}
	if (!ft_strcmp(args[0], "unset"))
	{
		custom_unset(data, args);
		return (1);
	}
	if (!ft_strcmp(args[0], "env"))
	{
		custom_env(data);
		return (1);
	}
	if (!ft_strcmp(args[0], "exit"))
	{
		clean_exit(data, args);
		return (1);
	}
	return (0);
}
