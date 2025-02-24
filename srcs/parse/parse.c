/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:30:35 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/24 19:23:19 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

int	parse(t_data *data)
{
	t_parser	*parser;

	parser = data->parser;
	if (split_cmd(parser))
		return (1);
	if (check_cmd(parser))
		return (1);
	print_tokens(parser->tokens);
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
		if (!(tokens[i]->type & (PIPE | OR | AND)))
		{
			curr_cmd->cmd_line = add_token(curr_cmd->cmd_line, tokens[i]);
			if (curr_cmd->cmd_line == NULL)
				return (print_error(ERR_MALLOC));
		}
		else if (tokens[i]->type & PIPE)
		{
			curr_cmd->success = create_node();
			curr_cmd->delimitter = PIPE;
			curr_cmd = curr_cmd->success;
		}
		else if (tokens[i]->type & AND)
		{
			curr_cmd->success = create_node();
			curr_cmd->delimitter = AND;
			curr_cmd = curr_cmd->success;
		}
		else if (tokens[i]->type & AND)
		{
			curr_cmd->failure = create_node();
			curr_cmd->delimitter = AND;
			curr_cmd = curr_cmd->failure;
		}
		i++;
	}
	return (0);
}
