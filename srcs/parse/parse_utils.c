/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:26:00 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/27 23:35:04 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>

static void	parse_cmd(t_token *token, t_token **root, t_token **last);
static void	parse_pipe(t_token *token, t_token **root, t_token **last);
static void	parse_redirect(t_token **tokens, int *i, t_token **root,
				t_token **last);
static void	parse_open(t_token **tokens, int *i, t_token **root,
				t_token **last);

t_token	*parse_line(t_token **tokens)
{
	t_token	*root;
	t_token	*last;
	int		i;

	i = 0;
	root = NULL;
	while (tokens[i] != NULL && !(tokens[i]->type & CLOSE))
	{
		if (tokens[i]->type & CMD)
			parse_cmd(tokens[i], &root, &last);
		else if (tokens[i]->type & DELIMITTER)
		{
			tokens[i]->left = root;
			root = tokens[i];
			last = tokens[i];
		}
		else if (tokens[i]->type & OPEN)
			parse_open(tokens, &i, &root, &last);
		else if (tokens[i]->sub_type & PIPE)
			parse_pipe(tokens[i], &root, &last);
		else if (tokens[i]->type & REDIRECT)
			parse_redirect(tokens, &i, &root, &last);
		i++;
	}
	return (root);
}

static void	parse_cmd(t_token *token, t_token **root, t_token **last)
{
	if (*root == NULL)
		*root = token;
	else if ((*last)->type & (DELIMITTER | REDIRECT))
		(*last)->right = token;
	*last = token;
}

static void	parse_redirect(t_token **tokens, int *i, t_token **root,
		t_token **last)
{
	if (*root == NULL)
		*root = tokens[*i];
	else
		(*last)->right = tokens[*i];
	tokens[*i]->left = tokens[*i + 1];
	*last = tokens[*i];
	(*i)++;
}

static void	parse_pipe(t_token *token, t_token **root, t_token **last)
{
	if ((*root)->type & (CMD | REDIRECT))
	{
		token->left = *root;
		*root = token;
	}
	else
	{
		token->left = *last;
		*root = token;
	}
	*last = token;
}

static void	parse_open(t_token **tokens, int *i, t_token **root, t_token **last)
{
	t_token	*tmp;
	int		parentesis;

	parentesis = 0;
	tmp = parse_line(&tokens[*i + 1]);
	if (*root == NULL)
		*root = tmp;
	else if ((*last)->type & (DELIMITTER | REDIRECT))
		(*last)->right = tmp;
	while (1)
	{
		count_parentesis(&parentesis, tokens[*i]);
		if (tokens[*i]->type & CLOSE && parentesis == 0)
			break ;
		(*i)++;
	}
	*last = tmp;
}
