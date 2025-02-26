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
#include <stdio.h>

static void	shift_redirect(t_token **tokens, int *index);
static void	organize_redirect(t_parser *parser, int *index);
static void	assign_index(t_parser *parser);

void	prepare_cmd(t_parser *parser)
{
	int		i;
	t_token	*current;

	i = 0;
	parser->last_token = START;
	while (parser->tokens[i] != NULL)
	{
		current = parser->tokens[i];
		if (current->sub_type & (APPEND | HERE_DOC | R_IN | R_OUT))
			organize_redirect(parser, &i);
		else if (current->sub_type & PIPE)
			current->type = REDIRECT;
		else if (current->sub_type & (AND | OR))
			current->type = DELIMITTER;
		else if (current->sub_type & (NAME))
			current->type = CMD;
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
	while (i >= 0 && tokens[i]->type & NAME)
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
	current = parser->tokens[*index];
	current->type = FILENAME;
	if (parser->tokens[*index - 1]->sub_type & HERE_DOC)
		current->type = LIMITER;
	if (parser->last_token & (NAME | FILENAME | LIMITER))
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
