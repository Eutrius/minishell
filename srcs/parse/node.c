/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:12:01 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/24 12:31:00 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

void	apply_tree(t_btree *root, void (*f)(void *));
void	free_node(void *node);

t_btree	*create_node(void)
{
	t_btree	*node;

	node = ft_calloc(1, sizeof(t_btree));
	if (node != NULL)
	{
		node->cmd_line = ft_calloc(1, sizeof(t_token *));
		if (node->cmd_line == NULL)
		{
			free(node);
			node = NULL;
		}
	}
	return (node);
}

void	free_node(void *node)
{
	free(((t_btree *)node)->cmd_line);
	free(node);
}

void	apply_tree(t_btree *root, void (*f)(void *))
{
	if (root == NULL)
		return ;
	apply_tree(root->success, f);
	apply_tree(root->failure, f);
	f(root);
}
