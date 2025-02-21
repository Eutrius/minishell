#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	custom_echo(t_data *data)
{
	t_token	**token;
	int		is_echo;

	token = data->cmd_line;
	is_echo = ft_strcmp(token[0]->content, "echo");
	if (!is_echo)
	{
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
}

void	clean_exit(t_data *data)
{
	int	is_exit;
	int	num_token;

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
		if (data->cmd_line[1] && !is_str_numeric(data->cmd_line[1]->content))
		{
			printf("B_Bros: exit: %s: numeric argument required\n",
				(char *)data->cmd_line[1]->content);
			exit(2);
		}
		if (data->cmd_line[1])
			exit(ft_atoi(data->cmd_line[1]->content));
		exit(0);
	}
}

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

void	custom_export(t_data *data)
{
	int	tokens_count;

	if (!ft_strcmp(data->cmd_line[0]->content, "export"))
	{
		tokens_count = count_tokens(data->cmd_line);
		if (tokens_count == 1)
			print_export(data);
	}
}
