#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static void	print_without_flag(t_token **token);
static void	print_with_flag(t_token **token);

void	custom_echo(t_data *data)
{
	t_token	**token;

	token = data->cmd_line;
	if (!token || !token[0])
		return ;
	if (!token[1])
	{
		printf("\n");
		return ;
	}
	if (token[1]->content && !ft_strcmp(token[1]->content, "-n") && !token[2])
		return ;
	if (token[1]->content && !ft_strcmp(token[1]->content, "-n"))
		print_with_flag(token);
	else if (token[1]->content && ft_strcmp(token[1]->content, "-n"))
		print_without_flag(token);
}

static void	print_with_flag(t_token **token)
{
	int	tokens_count;
	int	i;

	i = 0;
	if (!token || !token[0] || !token[1])
		return ;
	tokens_count = count_tokens(token);
	if (tokens_count >= 2)
	{
		i = 2;
		while (i < tokens_count)
		{
			if (token[i]->content)
			{
				printf("%s", (char *)token[i]->content);
				if (token[i + 1])
					printf(" ");
			}
			i++;
		}
		return ;
	}
}

static void	print_without_flag(t_token **token)
{
	int	tokens_count;
	int	i;

	i = 0;
	tokens_count = count_tokens(token);
	if (tokens_count >= 2)
	{
		i = 1;
		while (i < tokens_count)
		{
			if (token[i]->content)
			{
				printf("%s", (char *)token[i]->content);
				if (token[i + 1])
					printf(" ");
			}
			i++;
		}
		printf("\n");
		return ;
	}
	if (tokens_count == 1)
		printf("%s\n", (char *)token[1]->content);
}
