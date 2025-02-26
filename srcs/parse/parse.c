/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:30:35 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/25 15:16:59 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	parse(t_data *data)
{
	t_parser	*parser;

	parser = data->parser;
	if (split_cmd(parser))
		return (1);
	if (check_cmd(parser))
		return (1);
	prepare_cmd(parser);
	print_tokens(parser->tokens);
	free(parser->buffer);
	data->cmd_line = parser->tokens;
	return (0);
}
