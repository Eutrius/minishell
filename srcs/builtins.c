#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	custom_echo(char *buf, void *content)
{
	if (!ft_strcmp(buf, "echo"))
		printf("%s\n", (char *)content);
}

void	clean_exit(char *buf)
{
	if (!ft_strcmp(buf, "exit"))
		exit(0);
}

void	custom_pwd(char *buf)
{
	if (!ft_strcmp(buf, "pwd"))
	{
		buf = getcwd(NULL, 0);
		if (buf == NULL)
		{
			perror("Error");
			return ;
		}
		printf("%s\n", buf);
		free(buf);
	}
}

void	custom_chdir(char *buf, char *path)
{
	if (!ft_strcmp(buf, "cd"))
	{
		if (chdir(path) == -1)
			perror("Error");
	}
}

void	custom_env(char *buf, char **env)
{
	int	i;

	i = 0;
	if (!ft_strcmp(buf, "env"))
	{
		while (env[i] != NULL)
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
}
