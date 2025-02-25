/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:30:35 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/24 23:26:59 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

int	parse(t_data *data)
{
	t_parser	*parser;

	parser = data->parser;
	if (split_cmd(parser))
		return (1);
	print_tokens(parser->tokens);
	if (check_cmd(parser))
		return (1);
	free(parser->buffer);
	return (0);
}

int	parse_cmd(t_parser *parser)
{
	t_token	**tokens;
	t_btree	*curr_cmd;
	int		i;

	tokens = parser->tokens;
	i = 0;
	curr_cmd = create_node();
	if (curr_cmd == NULL)
		return (print_error(ERR_MALLOC));
	parser->parentesis = 0;
	while (tokens[i] != NULL)
	{
		i++;
	}
	return (0);
}
