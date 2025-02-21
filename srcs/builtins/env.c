#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	custom_env(t_data *data)
{
	int	i;

	if (!ft_strcmp(data->cmd_line[0]->content, "env"))
	{
		i = 0;
		while (data->env && data->env[i] != NULL)
		{
			printf("%s\n", data->env[i]);
			i++;
		}
	}
}
