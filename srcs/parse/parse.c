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

static void		print_tree(t_token *root);
static t_token	*parse_cmd(t_token **tokens);

int	parse(t_data *data)
{
	t_parser	*parser;
	t_token		*root;

	parser = data->parser;
	if (split_cmd(parser) || check_cmd(parser))
	{
		free(parser->buffer);
		parser->buffer = NULL;
		return (1);
	}
	prepare_cmd(parser);
	print_tokens(parser->tokens);
	printf("\n");
	root = parse_cmd(parser->tokens);
	printf("root: %s \n", (char *)root->content);
	print_tree(root);
	printf("\n");
	free(parser->buffer);
	data->cmd_line = parser->tokens;
	return (0);
}

static t_token	*parse_cmd(t_token **tokens)
{
	t_token	*root;
	t_token	*last_token;
	t_token	*tmp;
	int		parentesis;
	int		i;

	i = 0;
	root = NULL;
	parentesis = 0;
	while (tokens[i] != NULL && !(tokens[i]->type & CLOSE))
	{
		if (tokens[i]->type & CMD)
		{
			if (root == NULL)
				root = tokens[i];
			else if (last_token->type & (DELIMITTER | REDIRECT))
				last_token->right = tokens[i];
			last_token = tokens[i];
		}
		else if (tokens[i]->type & DELIMITTER)
		{
			tokens[i]->left = root;
			root = tokens[i];
			last_token = tokens[i];
		}
		else if (tokens[i]->type & OPEN)
		{
			tmp = parse_cmd(&tokens[i + 1]);
			if (root == NULL)
				root = tmp;
			else if (last_token->type & (DELIMITTER | REDIRECT))
				last_token->right = tmp;
			while (1)
			{
				count_parentesis(&parentesis, tokens[i]);
				if (tokens[i]->type & CLOSE && parentesis == 0)
					break ;
				i++;
			}
			i++;
			last_token = tmp;
			continue ;
		}
		else if (tokens[i]->type & REDIRECT)
		{
			if (root == NULL)
				root = tokens[i];
			else
				last_token->right = tokens[i];
			tokens[i]->left = tokens[i + 1];
			last_token = tokens[i];
			i += 2;
			continue ;
		}
		i++;
	}
	return (root);
}

static void	print_tree(t_token *root)
{
	if (root)
	{
		print_tree(root->left);
		printf("%s ", (char *)root->content);
		print_tree(root->right);
	}
}
