/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:30:35 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/28 23:52:07 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int	expand_vars(t_parser *parser);

int	parse(t_data *data)
{
	t_parser	*parser;
	t_token		*root;

	parser = data->parser;
	if (split_line(parser) || check_line(parser) || expand_vars(parser))
	{
		free(parser->buffer);
		parser->buffer = NULL;
		return (1);
	}
	prepare_line(parser);
	root = parse_line(parser->tokens);
	/*printf("\nTokens:\n");*/
	print_tokens(parser->tokens);
	/*printf("\n");*/
	/*printf("line: %s \n", parser->buffer);*/
	/*print_tree(root, 0);*/
	/*printf("\n");*/
	data->cmd_line = parser->tokens;
	data->root = root;
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
