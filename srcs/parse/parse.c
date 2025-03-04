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

static int	expand_vars(t_parser *parser);
static void	print_debug(t_data *data);

int	parse(t_data *data)
{
	t_parser	*parser;

	parser = data->parser;
	if (split_line(parser) || check_line(parser) || expand_vars(parser))
	{
		free(parser->buffer);
		parser->buffer = NULL;
		return (1);
	}
	prepare_line(parser);
	data->root = parse_line(parser->tokens);
	if (data->root == NULL)
		return (1);
	if (data->debug)
		print_debug(data);
	data->cmd_line = parser->tokens;
	parser->tokens = NULL;
	free(parser->buffer);
	return (0);
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

static int	expand_vars(t_parser *parser)
{
	int		i;
	char	*tmp;
	t_token	*curr_token;

	i = 0;
	tmp = NULL;
	while (parser->tokens[i] != NULL)
	{
		curr_token = parser->tokens[i];
		if (curr_token->type & (CMD | FILENAME))
		{
			tmp = expand_var(curr_token->content);
			if (tmp == NULL)
				return (1);
			free(curr_token->content);
			curr_token->content = tmp;
		}
		i++;
	}
	return (0);
}

static void	print_debug(t_data *data)
{
	print_tokens(data->parser->tokens);
	printf("\n");
	printf("line: %s \n", data->parser->buffer);
	print_tree(data->root, 0);
	printf("\n");
}
