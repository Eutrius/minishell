#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	custom_pwd(void)
{
	char	*buf;

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
