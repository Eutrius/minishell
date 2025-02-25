/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:44:14 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/25 17:25:48 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	count_cmd(t_parser *parser);
int	extract_cmd(t_token **tokens, int *index, t_btree *node);

int	merge_cmd(t_parser *parser)
{
	int	index;
	int	i;

	i = 0;
	index = 0;
	parser->nodes = create_nodes(count_cmd(parser));
	if (parser->nodes == NULL)
		return (print_error(ERR_MALLOC));
	while (parser->tokens[i] != NULL)
	{
		if (parser->tokens[i]->type & NAME)
		{
			if (extract_cmd(parser->tokens, &i, parser->nodes[index]))
				return (1);
			index++;
		}
		else
			i++;
	}
	return (0);
}

int	extract_cmd(t_token **tokens, int *index, t_btree *node)
{
	while (tokens[*index] != NULL
		&& !(tokens[*index]->type & (PIPE | AND | OR | OPEN | CLOSE)))
	{
		node->cmd_line = add_token(node->cmd_line, tokens[*index]);
		if (node->cmd_line == NULL)
			return (print_error(ERR_MALLOC));
		(*index)++;
	}
	return (0);
}

int	count_cmd(t_parser *parser)
{
	int		i;
	int		count;
	t_type	curr_type;

	i = 0;
	count = 0;
	parser->last_token = START;
	while (parser->tokens[i] != NULL)
	{
		curr_type = parser->tokens[i]->type;
		if (curr_type & NAME && !(parser->last_token & NAME))
			count++;
		else if (curr_type & (R_IN | R_OUT | APPEND | HERE_DOC))
			i++;
		parser->last_token = curr_type;
		i++;
	}
	return (count);
}
