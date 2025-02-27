/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:01:15 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/27 23:35:14 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stddef.h>

static int	skip_space(t_parser *parser, int *index);

int	split_line(t_parser *parser)
{
	int	i;

	i = 0;
	parser->last_token = START;
	parser->tokens = ft_calloc(1, sizeof(t_token *));
	if (parser->tokens == NULL)
		return (print_error(ERR_MALLOC));
	while (parser->buffer && parser->buffer[i] != '\0')
	{
		if (skip_space(parser, &i))
			continue ;
		if (is_dquote(parser->buffer[i]))
			extract(parser, &i, is_dquote, QUOTE);
		else if (is_quote(parser->buffer[i]))
			extract(parser, &i, is_quote, QUOTE);
		else if (is_special(parser->buffer[i]))
			extract(parser, &i, NULL, OPERATOR);
		else
			extract(parser, &i, is_special, NORMAL);
		if (parser->tokens == NULL)
			return (1);
	}
	return (0);
}

static int	skip_space(t_parser *parser, int *index)
{
	if (parser->buffer[*index] == ' ')
	{
		(*index)++;
		if (parser->last_token & (CMD | FILENAME | LIMITER | NONE))
			parser->last_token = NONE;
		return (1);
	}
	return (0);
}
