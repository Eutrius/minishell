#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

int	main(void)
{
	char	*buf;
	t_data	data;

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
