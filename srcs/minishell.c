#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
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
		parse_cmd(&data);
		// print_tokens(data.cmd);
		custom_echo(&data);
		clean_exit(&data);
		custom_pwd(&data);
		custom_chdir(&data);
		custom_env(&data);
		free(buf);
	}
}
