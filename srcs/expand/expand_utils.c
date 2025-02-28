/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:05:18 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/28 23:05:19 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

char	*safe_join(char *s1, char *s2)
{
	char	*res;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return ((s1));
	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

int	is_valid(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}
