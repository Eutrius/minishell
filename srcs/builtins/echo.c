#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static void	print_without_flag(char **args);
static void	print_with_flag(char **args);

void	custom_echo(char **args)
{
	if (!args || !args[0])
		return ;
	if (!args[1])
	{
		printf("\n");
		return ;
	}
	if (args[1] && !ft_strcmp(args[1], "-n") && !args[2])
		return ;
	if (args[1] && !ft_strcmp(args[1], "-n"))
		print_with_flag(args);
	else if (args[1] && ft_strcmp(args[1], "-n"))
		print_without_flag(args);
}

static void	print_with_flag(char **args)
{
	int	tokens_count;
	int	i;

	i = 0;
	if (!args || !args[0] || !args[1])
		return ;
	tokens_count = ft_strslen(args);
	if (tokens_count >= 2)
	{
		i = 2;
		while (i < tokens_count)
		{
			if (args[i])
			{
				printf("%s", args[i]);
				if (args[i + 1])
					printf(" ");
			}
			i++;
		}
		return ;
	}
}

static void	print_without_flag(char **args)
{
	int	tokens_count;
	int	i;

	i = 0;
	tokens_count = ft_strslen(args);
	if (tokens_count >= 2)
	{
		i = 1;
		while (i < tokens_count)
		{
			if (args[i])
			{
				printf("%s", args[i]);
				if (args[i + 1])
					printf(" ");
			}
			i++;
		}
		printf("\n");
		return ;
	}
	if (tokens_count == 1)
		printf("%s\n", args[1]);
}
