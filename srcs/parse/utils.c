/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:33:10 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/24 20:04:08 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
	free(parser->str);
	parser->str = NULL;
}

void	count_parentesis(int *parentesis, t_token *c_token)
{
	if (c_token->sub_type & OPEN)
		(*parentesis)++;
	if (c_token->sub_type & CLOSE)
		(*parentesis)--;
}
