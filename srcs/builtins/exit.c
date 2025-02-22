#include "libft.h"
#include "minishell.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	clean_exit(t_data *data)
{
	int			is_exit;
	int			num_token;
	long long	code;

	is_exit = ft_strcmp(data->cmd_line[0]->content, "exit");
	if (!is_exit)
	{
		printf("exit\n");
		num_token = count_tokens(data->cmd_line);
		if (num_token > 2)
		{
			printf("B_bros: exit: too many arguments\n");
			g_status = 255;
			return ;
		}
		if ((data->cmd_line[1] && !is_str_numeric(data->cmd_line[1]->content))
			|| (!ft_atoll(data->cmd_line[1]->content, &code)))
		{
			printf("B_Bros: exit: %s: numeric argument required\n",
				(char *)data->cmd_line[1]->content);
			exit(2);
		}
		if (data->cmd_line[1])
			exit(ft_atoi(data->cmd_line[1]->content));
		ft_free_strs(data->env);
		exit(0);
	}
}
