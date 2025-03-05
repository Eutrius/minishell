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
	if (token->sub_type & LIMITER)
	{
		if (token->content != NULL)
			close(*(int *)token->content);
	}
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

t_token	**add_token(t_token **tokens, t_token *token)
{
	int		len;
	t_token	**res;

	len = 0;
	while (tokens[len] != NULL)
		len++;
	res = ft_calloc(len + 2, sizeof(t_token *));
	if (res == NULL)
	{
		free_tokens(tokens);
		return (NULL);
	}
	res[len] = token;
	len--;
	while (len >= 0)
	{
		res[len] = tokens[len];
		len--;
	}
	free(tokens);
	return (res);
}
