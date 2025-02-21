#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	custom_chdir(t_data *data)
{
	int	tokens_count;

	if (!ft_strcmp(data->cmd_line[0]->content, "cd"))
	{
		tokens_count = count_tokens(data->cmd_line);
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
		if (data->cmd_line[1] && chdir(data->cmd_line[1]->content) == -1)
		{
			g_status = 1;
			perror("Error");
		}
	}
}
