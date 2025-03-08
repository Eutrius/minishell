/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:40:21 by jyriarte          #+#    #+#             */
/*   Updated: 2025/03/04 13:32:02 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int	check_type(t_token *c_token, t_token *n_token);
static int	unexpected_error(char *content);

int	check_line(t_parser *parser)
{
	int	i;

	i = 0;
	parser->parentesis = 0;
	if (check_type(NULL, parser->tokens[i]))
		return (unexpected_error(parser->tokens[i]->content));
	while (parser->tokens[i] != NULL)
	{
		count_parentesis(&parser->parentesis, parser->tokens[i]);
		if (parser->parentesis < 0)
			return (unexpected_error(")"));
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
		return (print_error1(ERR_SYNTAX, ": unexpected end of file", 2));
	return (expand_vars(parser));
}

static int	check_type(t_token *c_token, t_token *n_token)
{
	t_type	current;
	t_type	next;

	current = START;
	if (c_token != NULL)
		current = c_token->sub_type;
	next = END;
	if (n_token != NULL)
		next = n_token->sub_type;
	if (current & (APPEND | R_IN | R_OUT))
		return (!(next & FILENAME));
	else if (current & HERE_DOC)
		return (!(next & LIMITER));
	else if (current & (PIPE | OR | AND | OPEN))
		return ((next & (PIPE | OR | AND | END | CLOSE)));
	else if (current & CLOSE)
		return (next & (CMD | OPEN));
	else if (current & CMD)
		return (next & (OPEN));
	else if (current & START)
		return (next & (PIPE | OR | AND | CLOSE));
	return (0);
}

static int	unexpected_error(char *content)
{
	g_status = 2;
	return (print_error3(ERR_SYNTAX, " near unexpected token `", content, "'"));
}
