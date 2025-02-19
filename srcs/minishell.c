#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char		*buf;
	t_data		data;
	extern char	**environ;
	char		**dup_env;

	(void)data;
	dup_env = ft_strsdup(environ);
	if (!dup_env)
		return (0);
	while (1)
	{
		buf = readline("B_Bros > ");
		add_history(buf);
		data.token = parse_cmd(buf);
		// print_tokens(data.cmd);
		custom_echo(buf, data.token[0]->content);
		clean_exit(buf);
		custom_pwd(buf);
		custom_chdir(buf, data.token[0]->content);
		custom_env(buf, environ);
		free(buf);
	}
}
