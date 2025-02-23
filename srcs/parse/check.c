/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:40:21 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/23 15:05:00 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

static int	check_type(t_token *c_token, t_token *n_token);
static void	count_parentesis(t_parser *parser, t_token *c_token);

int	check_cmd(t_parser *parser)
{
	int	i;

	i = 0;
	parser->parentesis = 0;
	if (check_type(NULL, parser->tokens[i]))
		return (print_error3(ERR_SYNTAX, " near unexpected token `",
				parser->tokens[i]->content, "'"));
	while (parser->tokens[i] != NULL)
	{
		count_parentesis(parser, parser->tokens[i]);
		if (check_type(parser->tokens[i], parser->tokens[i + 1]))
		{
			if (parser->tokens[i + 1])
				return (print_error3(ERR_SYNTAX, " near unexpected token `",
						parser->tokens[i + 1]->content, "'"));
			else
				return (print_error1(ERR_SYNTAX,
						" near unexpected token `newline'"));
		}
		i++;
	}
	if (parser->parentesis != 0)
		return (print_error1(ERR_SYNTAX, ": unexpected end of file"));
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
	else if (current & (PIPE | OR | AND))
		return (!(next & (NAME | OPEN)));
	else if (current & OPEN)
		return (next & (CLOSE | PIPE | OR | AND | END));
	else if (current & CLOSE)
		return (next & (NAME | OPEN));
	else if (current & NAME)
		return (next & OPEN);
	else if (current & START)
		return (next & (PIPE | OR | AND | CLOSE));
	return (0);
}

static void	count_parentesis(t_parser *parser, t_token *c_token)
{
	if (c_token->type & OPEN)
		parser->parentesis++;
	if (c_token->type & CLOSE)
		parser->parentesis--;
}
