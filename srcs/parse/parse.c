/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:30:35 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/20 17:50:53 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

static void	tokenize(t_data *data);

void	parse_cmd(t_data *data)
{
	t_parser	*parser;

	parser = data->parser;
	split_cmd(parser);
	if (!parser->strs)
		return ;
	tokenize(data);
	print_tokens(data->cmd_line);
	free(parser->buffer);
	// ft_free_strs(parser->strs);
	parser->strs = NULL;
}

static void	tokenize(t_data *data)
{
	t_parser	*parser;
	int			i;
	char		*content;

	parser = data->parser;
	data->cmd_line = ft_calloc(ft_strslen(parser->strs) + 1, sizeof(t_token *));
	if (!data->cmd_line)
		return ;
	i = 0;
	content = parser->strs[i];
	while (content != NULL)
	{
		content = parser->strs[i];
		if (parser->skipped)
		{
			data->cmd_line[i] = create_token(content, CMD);
			parser->skipped = 0;
		}
		else
			data->cmd_line[i] = assign_token(parser->strs[i]);
		i++;
	}
}
