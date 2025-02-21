#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	custom_pwd(t_data *data)
{
	char	*buf;

	if (!ft_strcmp(data->cmd_line[0]->content, "pwd"))
	{
		buf = getcwd(NULL, 0);
		if (buf == NULL)
		{
			perror("Error");
			g_status = 1;
			return ;
		}
		printf("%s\n", buf);
		free(buf);
	}
}
