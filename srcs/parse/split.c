/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:01:15 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/20 17:58:25 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

static int	skip_space(t_parser *parser, int *index);

void	split_cmd(t_parser *parser)
{
	int	i;

	parser->strs = ft_calloc(1, sizeof(char *));
	if (parser->strs == NULL)
		parse_strs_error(&parser->strs, ERR_MALLOC);
	i = 0;
	parser->skipped = 1;
	while (parser->strs && parser->buffer[i] != '\0')
	{
		if (skip_space(parser, &i))
			continue ;
		if (is_dquote(parser->buffer[i]))
			extract_str(parser, &i, is_dquote, DQUOTE);
		else if (is_quote(parser->buffer[i]))
			extract_str(parser, &i, is_quote, QUOTE);
		else if (is_special(parser->buffer[i]))
			extract_op(parser, &i);
		else
			extract_str(parser, &i, is_special, NORMAL);
	}
	parser->skipped = 1;
}

static int	skip_space(t_parser *parser, int *index)
{
	if (parser->buffer[*index] == ' ')
	{
		(*index)++;
		parser->skipped = 1;
		return (1);
	}
	return (0);
}
