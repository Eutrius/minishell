#include "../includes/minishell.h"
// clang-format off
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
// clang-format on
#include <stdlib.h>

static void	read_line(t_data *data);

int	main(void)
{
	static t_data	data;
	static t_parser	parser;

	init(&data, &parser);
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
