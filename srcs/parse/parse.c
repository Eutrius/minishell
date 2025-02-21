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
	// print_tokens(data->cmd_line);
	// free(parser->buffer);
	// ft_free_strs(parser->strs);
	parser->strs = NULL;
}

static void	tokenize(t_data *data)
{
	t_parser	*parser;
	int			i;

	parser = data->parser;
	data->cmd_line = ft_calloc(ft_strslen(parser->strs) + 1, sizeof(t_token *));
	if (!data->cmd_line)
		return ;
	i = 0;
	while (parser->strs[i] != NULL)
	{
		data->cmd_line[i] = assign_token(data->cmd_line, parser->strs[i], i);
		i++;
	}
}
