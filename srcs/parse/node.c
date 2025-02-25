/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:12:01 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/25 16:36:52 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

void	apply_tree(t_btree *root, void (*f)(void *));
void	free_node(void *node);

t_btree	*create_node(int id)
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
	node->id = id;
	return (node);
}

t_btree	**create_nodes(int size)
{
	t_btree	**nodes;
	int		i;

	nodes = ft_calloc(size, sizeof(t_btree *));
	if (nodes == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		nodes[i] = create_node(i);
		if (nodes[i] == NULL)
		{
			free_nodes(nodes);
			return (NULL);
		}
		i++;
	}
	return (nodes);
}

void	free_nodes(t_btree **nodes)
{
	int	i;

	i = 0;
	while (nodes[i] != NULL)
	{
		free_node(nodes[i]);
		i++;
	}
	free(nodes);
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
