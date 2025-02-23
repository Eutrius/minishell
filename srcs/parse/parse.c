/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:30:35 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/23 13:07:00 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

void	parse_cmd(t_data *data)
{
	t_parser	*parser;

	parser = data->parser;
	if (split_cmd(parser))
		return ;
	if (check_cmd(parser))
		return ;
	print_tokens(parser->tokens);
	free(parser->buffer);
}

void	parse_error(t_parser *parser)
{
	free_tokens(parser->tokens);
	parser->tokens = NULL;
	free(parser->str);
	parser->str = NULL;
	free(parser->buffer);
	parser->str = NULL;
}

int	gen_token(t_parser *parser, t_mode mode)
{
	if (mode != OPERATOR)
		parser->token = create_token(parser->str, NAME);
	else if (!ft_strcmp(parser->str, "||"))
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
	if (parser->token == NULL)
		return (print_error(ERR_MALLOC));
	return (0);
}
