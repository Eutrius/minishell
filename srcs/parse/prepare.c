/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:44:14 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/28 23:46:53 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static void	shift_redirect(t_token **tokens, int *index);
static int	prepare_redirect(t_parser *parser, int *index, t_token *current);
static void	assign_index(t_parser *parser);

int	prepare_line(t_parser *parser)
{
	int		i;
	t_token	*current;

	i = 0;
	if (split_line(parser))
		return (1);
	parser->last_token = START;
	while (parser->tokens[i] != NULL)
	{
		current = parser->tokens[i];
		if (current->sub_type & (APPEND | HERE_DOC | R_IN | R_OUT))
		{
			if (prepare_redirect(parser, &i, current))
				return (1);
		}
		else if (current->sub_type & PIPE)
			current->type = REDIRECT;
		else if (current->sub_type & (AND | OR))
			current->type = DELIMITER;
		parser->last_token = parser->tokens[i]->type;
		i++;
	}
	assign_index(parser);
	return (0);
}

static int	prepare_redirect(t_parser *parser, int *index, t_token *current)
{
	if (current->sub_type & HERE_DOC)
	{
		if (heredoc(parser->tokens[*index + 1]))
			return (1);
	}
	current->type = REDIRECT;
	(*index)++;
	if (parser->last_token & (CMD))
		shift_redirect(parser->tokens, index);
	return (0);
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
