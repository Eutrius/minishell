#include "libft.h"
#include "minishell.h"
// clang-format off
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
// clang-format on
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	read_line(t_data *data);

int			g_status;

int	main(void)
{
	static t_data	data;
	static t_parser	parser;

	init(&data, &parser);
	while (1)
	{
		read_line(&data);
		if (parser.buffer == NULL || ft_strlen(parser.buffer) == 0)
			continue ;
		if (!ft_strcmp("debug", parser.buffer))
		{
			if (data.debug)
				data.debug = 0;
			else
				data.debug = 1;
			free(parser.buffer);
			parser.buffer = NULL;
			continue ;
		}
		if (parse(&data, &parser))
			continue ;
		executor(&data, data.root);
		free_tokens(data.tokens);
		dup2(data.stdin_orig, STDIN_FILENO);
		dup2(data.stdout_orig, STDOUT_FILENO);
	}
	exit(0);
}

static void	read_line(t_data *data)
{
	if (data->debug)
		data->parser->buffer = readline("debug > ");
	else
		data->parser->buffer = readline("bashbros > ");
	add_history(data->parser->buffer);
}
