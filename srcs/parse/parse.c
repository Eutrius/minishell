/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:30:35 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/27 23:33:25 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	parse(t_data *data)
{
	t_parser	*parser;
	t_token		*root;

	parser = data->parser;
	if (split_line(parser) || check_line(parser))
	{
		free(parser->buffer);
		parser->buffer = NULL;
		return (1);
	}
	prepare_line(parser);
	// printf("\nTokens:\n");
	// print_tokens(parser->tokens);
	// printf("\n");
	root = parse_line(parser->tokens);
	// printf("line: %s \n", parser->buffer);
	print_tree(root, 0);
	printf("\n");
	data->cmd_line = parser->tokens;
	data->root = root;
	free(parser->buffer);
	return (0);
}
