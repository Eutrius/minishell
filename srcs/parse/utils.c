/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:33:10 by jyriarte          #+#    #+#             */
/*   Updated: 2025/03/04 13:50:08 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	is_special(int c)
{
	if (c == ' ')
		return (1);
	else if (c == '|')
		return (1);
	else if (c == '&')
		return (1);
	else if (c == '<')
		return (1);
	else if (c == '>')
		return (1);
	else if (is_quote(c))
		return (1);
	else if (is_dquote(c))
		return (1);
	else if (c == '(')
		return (1);
	else if (c == ')')
		return (1);
	return (0);
}

int	is_quote(int c)
{
	if (c == '\'')
		return (1);
	return (0);
}

int	is_dquote(int c)
{
	if (c == '"')
		return (1);
	return (0);
}

void	parse_error(t_parser *parser)
{
	free_tokens(parser->tokens);
	parser->tokens = NULL;
	parser->token = NULL;
	free(parser->str);
	parser->str = NULL;
	free(parser->buffer);
	parser->buffer = NULL;
}

void	count_parentesis(int *parentesis, t_token *token)
{
	if (token->sub_type & OPEN)
		(*parentesis)++;
	if (token->sub_type & CLOSE)
		(*parentesis)--;
}
