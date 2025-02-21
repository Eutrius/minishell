#include "../includes/minishell.h"
#include "../libft/libft.h"
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
		num_token = token_count(data->cmd_line);
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

// void	custom_pwd(t_data *data)
// {
//   (void )data;
// 	// if (!ft_strcmp(buf, "pwd"))
// 	// {
// 	// 	buf = getcwd(NULL, 0);
// 	// 	if (buf == NULL)
// 	// 	{
// 	// 		perror("Error");
// 	// 		return ;
// 	// 	}
// 	// 	printf("%s\n", buf);
// 	// 	free(buf);
// 	// }
// }

// void	custom_chdir(t_data *data)
// {
//   (void )data;
// 	// if (!ft_strcmp(buf, "cd"))
// 	// {
// 	// 	if (chdir(path) == -1)
// 	// 		perror("Error");
// 	// }
// }

// void	custom_env(t_data *data)
// {
//   (void )data;
// 	// int	i;

// 	// i = 0;
// 	// if (!ft_strcmp(buf, "env"))
// 	// {
// 	// 	while (env[i] != NULL)
// 	// 	{
// 	// 		printf("%s\n", env[i]);
// 	// 		i++;
// 	// 	}
// 	// }
// }
