#include "libft.h"
#include "minishell.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	clean_exit(t_data *data)
{
	int	num_token;

	printf("exit\n");
	num_token = count_tokens(data->cmd_line);
	if (num_token > 2)
	{
		printf("B_bros: exit: too many arguments\n");
		g_status = 255;
		return ;
	}
	if (num_token == 2 && data->cmd_line[1])
	{
		if (!check_exit_value(data->cmd_line[1]->content))
		{
			printf("B_Bros: exit: %s: numeric argument required\n",
				(char *)data->cmd_line[1]->content);
			exit(2);
		}
	}
	if (data->cmd_line[1])
		exit(ft_atoi(data->cmd_line[1]->content));
	ft_free_strs(data->env);
	exit(0);
}
