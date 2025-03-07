#include "libft.h"
#include "minishell.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	clean_exit(t_data *data, char **args)
{
	int	num_token;

	printf("exit\n");
	num_token = ft_strslen(args);
	if (num_token > 2)
	{
		printf("B_bros: exit: too many arguments\n");
		g_status = 255;
		return ;
	}
	if (num_token == 2 && args[1])
	{
		if (!check_exit_value(args[1]))
		{
			free_memory(data, args);
			printf("B_Bros: exit: %s: numeric argument required\n", args[1]);
			exit(2);
		}
	}
	if (args[1])
	{
		free_memory(data, args);
		exit(ft_atoi(args[1]));
	}
	free_memory(data, args);
	exit(0);
}
