#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	custom_chdir(char **args)
{
	int	tokens_count;

	tokens_count = ft_strslen(args);
	if (tokens_count == 1 && chdir(getenv("HOME")) == -1)
	{
		g_status = 1;
		perror("Error");
		return ;
	}
	if (tokens_count > 2)
	{
		printf("B_Bros: cd: too many arguments");
		g_status = 1;
		return ;
	}
	if (args[1] && chdir(args[1]) == -1)
	{
		g_status = 1;
		perror("Error");
	}
}
