#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*buf;
	t_data	data;

	(void)data;
	while (1)
	{
		buf = readline("B_Bros > ");
		add_history(buf);
		data.cmd = parse_cmd(buf);
		print_tokens(data.cmd);
		custom_echo(buf, data.cmd[0]->content);
		clean_exit(buf);
		custom_pwd(buf);
		custom_chdir(buf, data.cmd[0]->content);
		free(buf);
		return (0);
	}
}
