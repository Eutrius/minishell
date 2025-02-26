/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:11:27 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/24 19:52:37 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

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
	return ("OTHERS");
}

void	print_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		printf("%i: %s: %s\n", tokens[i]->index, get_enum(tokens[i]->sub_type),
			(char *)tokens[i]->content);
		i++;
	}
}
