#include "../libft/libft.h"
#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	custom_echo(t_data *data)
{
  t_token **token = data->cmd_line;
  if (!token || !token[0])
    return ;
  if (token[0] && !token[1])
  {
    printf("\n");
    return;
  }
  find_guard(token[1]->content);
  printf("%s\n",(char *)token[1]->content);
}

void	clean_exit(t_data *data)
{

  (void )data;
	// if (!ft_strcmp(buf, "exit"))
		// exit(0);
}

void	custom_pwd(t_data *data)
{
  (void )data;
	// if (!ft_strcmp(buf, "pwd"))
	// {
	// 	buf = getcwd(NULL, 0);
	// 	if (buf == NULL)
	// 	{
	// 		perror("Error");
	// 		return ;
	// 	}
	// 	printf("%s\n", buf);
	// 	free(buf);
	// }
}

void	custom_chdir(t_data *data)
{
  (void )data;
	// if (!ft_strcmp(buf, "cd"))
	// {
	// 	if (chdir(path) == -1)
	// 		perror("Error");
	// }
}

void	custom_env(t_data *data)
{
  (void )data;
	// int	i;

	// i = 0;
	// if (!ft_strcmp(buf, "env"))
	// {
	// 	while (env[i] != NULL)
	// 	{
	// 		printf("%s\n", env[i]);
	// 		i++;
	// 	}
	// }
}
