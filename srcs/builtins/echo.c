#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

void	custom_echo(t_data *data)
{
	t_token	**token;

	token = data->cmd_line;
	if (!token || !token[0])
		return ;
	if (token[0] && !token[1])
	{
		printf("\n");
		return ;
	}
	if (token[0] && !ft_strcmp(token[1]->content, "-n") && !token[2])
		return ;
	if (token[0] && !ft_strcmp(token[1]->content, "-n") && token[2])
	{
		printf("%s", (char *)token[2]->content);
		return ;
	}
	printf("%s\n", (char *)token[1]->content);
}
