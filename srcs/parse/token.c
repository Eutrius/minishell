/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:57:19 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/27 23:36:05 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

t_token	*create_token(void *content, t_type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = content;
	token->sub_type = type;
	token->type = type;
	return (token);
}

void	free_token(t_token *token)
{
	if (!token)
		return ;
	free(token->content);
	free(token);
}

void	free_tokens(t_token **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i] != NULL)
	{
		free_token(tokens[i]);
		i++;
	}
	free(tokens);
}

void	close_limiters(t_token **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i] != NULL)
	{
		if (tokens[i]->sub_type & LIMITER)
		{
			if (tokens[i]->content != NULL)
			{
				if (close(*(int *)tokens[i]->content) == -1)
					print_error(ERR_CLOSEFD, 1);
			}
		}
		i++;
	}
}
