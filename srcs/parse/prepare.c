/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:44:14 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/27 23:33:40 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static void	shift_redirect(t_token **tokens, int *index);
static void	organize_redirect(t_parser *parser, int *index);
static void	assign_index(t_parser *parser);

void	prepare_line(t_parser *parser)
{
	int		i;
	t_token	*current;

	i = 0;
	parser->last_token = START;
	while (parser->tokens[i] != NULL)
	{
		current = parser->tokens[i];
		if (current->sub_type & (APPEND | HERE_DOC | R_IN | R_OUT))
		{
			organize_redirect(parser, &i);
			parser->last_token = parser->tokens[i]->type;
			i++;
			continue ;
		}
		else if (current->sub_type & PIPE)
			current->type = REDIRECT;
		else if (current->sub_type & (AND | OR))
			current->type = DELIMITTER;
		parser->last_token = current->type;
		i++;
	}
	assign_index(parser);
}

static void	shift_redirect(t_token **tokens, int *index)
{
	t_token	*redirect;
	t_token	*name;
	int		i;
	int		count;

	i = *index - 2;
	name = tokens[*index];
	redirect = tokens[*index - 1];
	count = 0;
	while (i >= 0 && tokens[i]->type & CMD)
	{
		tokens[*index - count] = tokens[i];
		i--;
		count++;
	}
	tokens[i + 1] = redirect;
	tokens[i + 2] = name;
}

static void	organize_redirect(t_parser *parser, int *index)
{
	t_token	*current;

	current = parser->tokens[*index];
	current->type = REDIRECT;
	(*index)++;
	if (parser->last_token & (CMD | FILENAME | LIMITER))
		shift_redirect(parser->tokens, index);
}

static void	assign_index(t_parser *parser)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = -1;
	while (parser->tokens[i] != NULL)
	{
		if (parser->tokens[i]->type & CMD)
		{
			if (tmp == -1)
				tmp = i;
			parser->tokens[i]->index = tmp;
		}
		else
		{
			tmp = -1;
			parser->tokens[i]->index = i;
		}
		i++;
	}
}
