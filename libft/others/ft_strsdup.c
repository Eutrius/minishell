/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:47:55 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/26 19:22:06 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	**ft_strsdup(char **strs)
{
	char	**dup;
	char	*str;
	size_t	i;

	i = 0;
	dup = ft_calloc(ft_strslen(strs) + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	while (strs[i] != NULL)
	{
		str = ft_strdup(strs[i]);
		if (!str)
		{
			ft_free_strs(dup);
			return (NULL);
		}
		dup[i] = str;
		i++;
	}
	return (dup);
}
