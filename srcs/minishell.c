#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>


int	main(void)
{
	char	*buf;
	t_data	data;
	t_token	**tokens;

	(void)data;
	while (1)
	{
		buf = readline("B_Bros > ");
		add_history(buf);
		tokens = parse_cmd(buf);
		print_tokens(tokens);
		custom_echo(buf, tokens[0]->content);
		clean_exit(buf);
		custom_pwd(buf);
		custom_chdir(buf, tokens[0]->content);
		free(tokens);


	while (1)
	{
		buf = readline("B_bros > ");
		if (!buf || !ft_strcmp(buf, "exit"))
			exit(0);
		add_history(buf);
		data.cmd = parse_cmd(buf);
		print_tokens(data.cmd);
		free(buf);
	}
	return (0);
}
