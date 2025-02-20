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

void	parse_cmd(t_data *data)
{
	int			i;
	t_parser	*parser;

	parser = data->parser;
	split_cmd(parser);
	if (!parser->strs)
		return ;
	i = 0;
	while (parser->strs[i] != NULL)
	{
		printf("%s\n", parser->strs[i]);
		i++;
	}
	free(parser->buffer);
	ft_free_strs(parser->strs);
	parser->strs = NULL;
}
