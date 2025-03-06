/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:26:00 by jyriarte          #+#    #+#             */
/*   Updated: 2025/03/04 11:48:23 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>

static void	parse_predirect(t_token **tokens, int *i, t_token **tmp);

void	parse_cmd(t_token *token, t_token **root, t_token **last)
{
	if (*root == NULL)
		*root = token;
	else if ((*last)->type & (DELIMITER | REDIRECT))
		(*last)->right = token;
	*last = token;
}

void	parse_redirect(t_token **tokens, int *i, t_token **root, t_token **last)
{
	if (*root == NULL)
		*root = tokens[*i];
	else
		(*last)->right = tokens[*i];
	tokens[*i]->left = tokens[*i + 1];
	*last = tokens[*i];
	(*i)++;
}

void	parse_pipe(t_token *token, t_token **root, t_token **last)
{
	if ((*root)->type & (CMD | REDIRECT))
	{
		token->left = *root;
		*root = token;
	}
	else
	{
		token->left = (*root)->right;
		(*root)->right = token;
	}
	*last = token;
}

void	parse_open(t_token **tokens, int *i, t_token **root, t_token **last)
{
	t_token	*tmp;
	int		parentesis;

	parentesis = 0;
	tmp = parse_line(&tokens[*i + 1]);
	while (1)
	{
		count_parentesis(&parentesis, tokens[*i]);
		if (tokens[*i]->type & CLOSE && parentesis == 0)
			break ;
		(*i)++;
	}
	parse_predirect(tokens, i, &tmp);
	if (*root == NULL)
		*root = tmp;
	else if ((*last)->type & (DELIMITER | REDIRECT | CMD))
		(*last)->right = tmp;
	*last = tmp;
}

static void	parse_predirect(t_token **tokens, int *i, t_token **tmp)
{
	t_token	*last_redirect;

	(*i)++;
	last_redirect = *tmp;
	while (tokens[*i]
		&& tokens[*i]->sub_type & (R_IN | R_OUT | APPEND | HERE_DOC))
	{
		if ((*tmp)->type & (DELIMITER | CMD) || (*tmp)->sub_type & PIPE)
		{
			tokens[*i]->right = *tmp;
			*tmp = tokens[*i];
		}
		else
		{
			tokens[*i]->right = last_redirect->right;
			last_redirect->right = tokens[*i];
		}
		last_redirect = tokens[*i];
		tokens[*i]->left = tokens[*i + 1];
		(*i) += 2;
	}
	(*i)--;
}
