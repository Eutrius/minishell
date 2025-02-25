/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:40:21 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/24 12:32:58 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int	check_type(t_token *c_token, t_token *n_token);
static int	unexpected_error(char *content);

int	check_cmd(t_parser *parser)
{
	int	i;

	i = 0;
	parser->parentesis = 0;
	if (check_type(NULL, parser->tokens[i]))
		return (unexpected_error(parser->tokens[i]->content));
	while (parser->tokens[i] != NULL)
	{
		count_parentesis(parser, parser->tokens[i]);
		if (check_type(parser->tokens[i], parser->tokens[i + 1]))
		{
			if (parser->tokens[i + 1])
				return (unexpected_error(parser->tokens[i + 1]->content));
			else
				return (unexpected_error("newline"));
		}
		i++;
	}
	if (parser->parentesis > 0)
		return (print_error1(ERR_SYNTAX, ": unexpected end of file"));
	else if (parser->parentesis < 0)
		return (unexpected_error(")"));
	return (0);
}

static int	check_type(t_token *c_token, t_token *n_token)
{
	t_type	current;
	t_type	next;

	current = START;
	if (c_token != NULL)
		current = c_token->type;
	next = END;
	if (n_token != NULL)
		next = n_token->type;
	if (current & (APPEND | HERE_DOC | R_IN | R_OUT))
		return (!(next & NAME));
	else if (current & (PIPE | OR | AND | OPEN))
		return ((next & (PIPE | OR | AND | END | CLOSE)));
	else if (current & CLOSE)
		return (next & (NAME | OPEN));
	else if (current & NAME)
		return (next & (OPEN));
	else if (current & START)
		return (next & (PIPE | OR | AND | CLOSE));
	return (0);
}

static int	unexpected_error(char *content)
{
	return (print_error3(ERR_SYNTAX, " near unexpected token `", content, "'"));
}
