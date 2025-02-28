/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:11:27 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/27 23:32:50 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static char	*get_more_enum(t_type type);

char	*get_enum(t_type type)
{
	if (type == NAME)
		return ("NAME");
	else if (type == OPEN)
		return ("OPEN");
	else if (type == CLOSE)
		return ("CLOSE");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == AND)
		return ("AND");
	else if (type == OR)
		return ("OR");
	else if (type == R_IN)
		return ("R_IN");
	else if (type == HERE_DOC)
		return ("HERE_DOC");
	else if (type == R_OUT)
		return ("R_OUT");
	else if (type == APPEND)
		return ("APPEND");
	return (get_more_enum(type));
}

static char	*get_more_enum(t_type type)
{
	if (type == CMD)
		return ("CMD");
	else if (type == DELIMITER)
		return ("DELIMITTER");
	else if (type == FILENAME)
		return ("FILENAME");
	else if (type == LIMITER)
		return ("LIMITER");
	else if (type == REDIRECT)
		return ("REDIRECT");
	else
		return ("OTHERS");
}

void	print_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		printf("%i: %s: %s: %s\n", tokens[i]->index, get_enum(tokens[i]->type),
			get_enum(tokens[i]->sub_type), (char *)tokens[i]->content);
		i++;
	}
}

void	print_tree(t_token *root, int level)
{
	int	i;

	if (root == NULL)
		return ;
	level += 5;
	print_tree(root->right, level);
	printf("\n");
	i = 5;
	while (i < level)
	{
		printf(" ");
		i++;
	}
	printf("%s\n", (char *)root->content);
	print_tree(root->left, level);
}
