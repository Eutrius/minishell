/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:30:35 by jyriarte          #+#    #+#             */
/*   Updated: 2025/03/04 13:53:08 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static void	print_debug(t_data *data, t_token *root);
static int	reset_parser(t_parser *parser, int return_value);

int	parse(t_data *data, t_parser *parser)
{
	t_token	*root;

	if (prepare_line(parser))
		return (reset_parser(parser, 1));
	root = parse_line(parser->tokens);
	if (root == NULL)
		return (reset_parser(parser, 1));
	if (data->debug)
	{
		print_debug(data, root);
		return (reset_parser(parser, 1));
	}
	data->tokens = parser->tokens;
	data->root = root;
	return (reset_parser(parser, 0));
}

t_token	*parse_line(t_token **tokens)
{
	t_token	*root;
	t_token	*last;
	int		i;

	i = 0;
	root = NULL;
	while (tokens[i] != NULL && !(tokens[i]->type & CLOSE))
	{
		if (tokens[i]->type & CMD)
			parse_cmd(tokens[i], &root, &last);
		else if (tokens[i]->type & DELIMITER)
		{
			tokens[i]->left = root;
			root = tokens[i];
			last = tokens[i];
		}
		else if (tokens[i]->type & OPEN)
			parse_open(tokens, &i, &root, &last);
		else if (tokens[i]->sub_type & PIPE)
			parse_pipe(tokens[i], &root, &last);
		else if (tokens[i]->type & REDIRECT)
			parse_redirect(tokens, &i, &root, &last);
		i++;
	}
	return (root);
}

static int	reset_parser(t_parser *parser, int return_value)
{
	if (return_value)
	{
		free_tokens(parser->tokens);
		free(parser->str);
	}
	parser->tokens = NULL;
	parser->token = NULL;
	parser->str = NULL;
	free(parser->buffer);
	parser->buffer = NULL;
	return (return_value);
}

static void	print_debug(t_data *data, t_token *root)
{
	print_tokens(data->parser->tokens);
	printf("\n");
	printf("line: %s \n", data->parser->buffer);
	print_tree(root, 0);
	printf("\n");
}
