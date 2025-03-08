/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:55:33 by jyriarte          #+#    #+#             */
/*   Updated: 2025/03/04 14:08:04 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int	extract_op(t_parser *parser, int *index);
static int	append_token(t_parser *parser);
static int	extract_str(t_parser *parser, int *index, int (*ctrl)(int),
				t_mode mode);

int	extract(t_parser *parser, int *index, int (*ctrl)(int), t_mode mode)
{
	int	status;

	if (mode == OPERATOR)
		status = extract_op(parser, index);
	else
		status = extract_str(parser, index, ctrl, mode);
	if (status)
		return (1);
	if ((parser->last_token & (CMD | FILENAME | LIMITER)) && mode != OPERATOR)
		return (join_last(parser));
	if (gen_token(parser, mode))
		return (1);
	return (append_token(parser));
}

static int	append_token(t_parser *parser)
{
	int		len;
	t_token	**res;

	len = 0;
	while (parser->tokens[len] != NULL)
		len++;
	res = ft_calloc(len + 2, sizeof(t_token *));
	if (res == NULL)
	{
		free(parser->token);
		parser->token = NULL;
		return (print_error(ERR_MALLOC, 1));
	}
	res[len] = parser->token;
	len--;
	while (len >= 0)
	{
		res[len] = parser->tokens[len];
		len--;
	}
	free(parser->tokens);
	parser->tokens = res;
	parser->last_token = parser->token->sub_type;
	return (0);
}

static int	extract_str(t_parser *parser, int *index, int (*ctrl)(int),
		t_mode mode)
{
	int	i;

	i = *index;
	if (mode != NORMAL)
		i++;
	while (parser->buffer[i] != '\0' && !(*ctrl)(parser->buffer[i]))
		i++;
	if (parser->buffer[i] == '\0' && mode != NORMAL)
		return (print_error1(ERR_SYNTAX, " unclosed quotes", 2));
	if (mode != NORMAL)
		i++;
	parser->str = ft_strndup(&parser->buffer[*index], i - *index);
	*index = i;
	if (parser->str == NULL)
		return (print_error(ERR_MALLOC, 1));
	return (0);
}

static int	extract_op(t_parser *parser, int *index)
{
	if (parser->buffer[*index] == '|')
		parser->str = if_double(parser->buffer, index, "||", "|");
	else if (parser->buffer[*index] == '(')
		parser->str = ft_strdup("(");
	else if (parser->buffer[*index] == ')')
		parser->str = ft_strdup(")");
	else if (parser->buffer[*index] == '>')
		parser->str = if_double(parser->buffer, index, ">>", ">");
	else if (parser->buffer[*index] == '<')
		parser->str = if_double(parser->buffer, index, "<<", "<");
	else if (!ft_strncmp(&parser->buffer[*index], "&&", 2))
	{
		(*index)++;
		parser->str = ft_strdup("&&");
	}
	else
		return (print_error1(ERR_SYNTAX, " near unexpected token `&'", 2));
	(*index)++;
	if (parser->str == NULL)
		return (print_error(ERR_MALLOC, 1));
	return (0);
}
