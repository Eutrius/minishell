/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:34:49 by lonulli           #+#    #+#             */
/*   Updated: 2025/03/07 22:34:50 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
// clang-format off
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
// clang-format on
#include <signal.h>
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
		if (set_signal(SIGQUIT, handle_quit))
		{
			free_memory(&data, NULL);
			print_error(ERR_SIGACTION, 1);
			exit(g_status);
		}
		executor(&data, data.root);
		free_tokens(data.tokens);
	}
	exit(0);
}

static void	read_line(t_data *data)
{
	if (set_signal(SIGQUIT, SIG_IGN))
	{
		free_memory(data, NULL);
		print_error(ERR_SIGACTION, 1);
		exit(g_status);
	}
	if (data->debug)
		data->parser->buffer = readline("debug > ");
	else
		data->parser->buffer = readline("bashbros > ");
	if (data->parser->buffer == NULL)
	{
		ft_free_strs(data->env);
		printf("exit\n");
		exit(0);
	}
	add_history(data->parser->buffer);
}
