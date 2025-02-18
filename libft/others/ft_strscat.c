/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strscat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:25:27 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/25 15:52:48 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_strscat(char **strs, char *str)
{
	size_t	strs_len;
	char	**res;
	int		i;

	i = 0;
	if (!strs)
		return (NULL);
	strs_len = ft_strslen(strs);
	res = ft_calloc(strs_len + 2, sizeof(char *));
	if (!res)
	{
		ft_free_strs(strs);
		return (NULL);
	}
	while (strs[i] != NULL)
	{
		res[i] = strs[i];
		i++;
	}
	res[i] = str;
	free(strs);
	return (res);
}
