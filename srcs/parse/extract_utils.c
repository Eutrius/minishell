/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:10:22 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/27 23:33:17 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

static void	gen_op_token(t_parser *parser);

char	*if_double(char *str, int *index, char *twice, char *once)
{
	if (!ft_strncmp(&str[*index], twice, 2))
	{
		(*index)++;
		return (ft_strdup(twice));
	}
	else
		return (ft_strdup(once));
}

void	join_last(t_parser *parser)
{
	char	*new_content;
	char	*old_content;

	old_content = parser->token->content;
	new_content = ft_strjoin(old_content, parser->str);
	if (new_content == NULL)
	{
		print_error(ERR_MALLOC);
		return (parse_error(parser));
	}
	parser->token->content = new_content;
	free(old_content);
	free(parser->str);
	parser->str = NULL;
}

int	gen_token(t_parser *parser, t_mode mode)
{
	if (mode != OPERATOR)
	{
		if (parser->last_token & (APPEND | R_IN | R_OUT))
			parser->token = create_token(parser->str, FILENAME);
		else if (parser->last_token & HERE_DOC)
			parser->token = create_token(parser->str, LIMITER);
		else
			parser->token = create_token(parser->str, CMD);
	}
	else
		gen_op_token(parser);
	if (parser->token == NULL)
		return (print_error(ERR_MALLOC));
	return (0);
}

static void	gen_op_token(t_parser *parser)
{
	if (!ft_strcmp(parser->str, "||"))
		parser->token = create_token(parser->str, OR);
	else if (!ft_strcmp(parser->str, "|"))
		parser->token = create_token(parser->str, PIPE);
	else if (!ft_strcmp(parser->str, "&&"))
		parser->token = create_token(parser->str, AND);
	else if (!ft_strcmp(parser->str, "("))
		parser->token = create_token(parser->str, OPEN);
	else if (!ft_strcmp(parser->str, ")"))
		parser->token = create_token(parser->str, CLOSE);
	else if (!ft_strcmp(parser->str, "<<"))
		parser->token = create_token(parser->str, HERE_DOC);
	else if (!ft_strcmp(parser->str, "<"))
		parser->token = create_token(parser->str, R_IN);
	else if (!ft_strcmp(parser->str, ">>"))
		parser->token = create_token(parser->str, APPEND);
	else
		parser->token = create_token(parser->str, R_OUT);
}
