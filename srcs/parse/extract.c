/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:55:33 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/20 17:34:57 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>

static char	*if_double(char *str, int *index, char *twice, char *once);
static void	join_last(t_parser *parser, char *str);
static char	*expand_variable(t_parser *parser, char *str);

void	extract_str(t_parser *parser, int *index, int (*f)(int), t_mode mode)
{
	int		i;
	char	*tmp;

	if (mode != NORMAL)
		(*index)++;
	i = *index;
	while (parser->buffer[i] != '\0' && !(*f)(parser->buffer[i]))
		i++;
	if (parser->buffer[i] == '\0' && mode != NORMAL)
		return (parse_strs_error(&parser->strs, ERR_SYNTAX));
	tmp = ft_strndup(&parser->buffer[*index], i - *index);
	if (mode == DQUOTE)
		tmp = expand_variable(parser, tmp);
	if (!tmp)
		return (parse_strs_error(&parser->strs, ERR_MALLOC));
	if (!parser->skipped)
		join_last(parser, tmp);
	else
		parser->strs = ft_strscat(parser->strs, tmp);
	if (parser->strs == NULL)
		print_error(ERR_MALLOC);
	parser->skipped = 0;
	*index = i;
	if (mode != NORMAL)
		(*index)++;
}

void	extract_op(t_parser *parser, int *index)
{
	char	*tmp;

	if (parser->buffer[*index] == '|')
		tmp = if_double(parser->buffer, index, "||", "|");
	else if (parser->buffer[*index] == '(')
		tmp = ft_strdup("(");
	else if (parser->buffer[*index] == ')')
		tmp = ft_strdup(")");
	else if (parser->buffer[*index] == '>')
		tmp = if_double(parser->buffer, index, ">>", ">");
	else if (parser->buffer[*index] == '<')
		tmp = if_double(parser->buffer, index, "<<", "<");
	else
		tmp = if_double(parser->buffer, index, "&&", "&");
	if (!tmp)
		return (parse_strs_error(&parser->strs, ERR_MALLOC));
	(*index)++;
	parser->skipped = 1;
	parser->strs = ft_strscat(parser->strs, tmp);
	if (parser->strs == NULL)
		print_error(ERR_MALLOC);
}

static char	*if_double(char *str, int *index, char *twice, char *once)
{
	if (!ft_strncmp(&str[*index], twice, 2))
	{
		(*index)++;
		return (ft_strdup(twice));
	}
	else
		return (ft_strdup(once));
}

static void	join_last(t_parser *parser, char *str)
{
	int		len;
	char	*last_str;

	len = ft_strslen(parser->strs);
	last_str = parser->strs[len - 1];
	parser->strs[len - 1] = ft_strjoin(last_str, str);
	if (parser->strs == NULL)
		parse_strs_error(&parser->strs, ERR_MALLOC);
	free(last_str);
	free(str);
}

static char	*expand_variable(t_parser *parser, char *str)
{
	(void)parser;
	return (str);
}
