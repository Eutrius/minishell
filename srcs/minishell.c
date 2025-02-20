#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

static void	read_line(t_data *data);

int	main(void)
{
	static t_data		data;
	static t_operators	operators;

	init(&data, &operators);
	while (1)
	{
		read_line(&data);
		parse_cmd(&data);
	}
	exit(0);
}

static void	read_line(t_data *data)
{
	data->buffer = readline("B_Bros > ");
	add_history(data->buffer);
}
