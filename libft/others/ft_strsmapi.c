/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsmapi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:19:40 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/20 12:34:26 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_strsmapi(char **strs, char *(*f)(char *))
{
	size_t	i;
	char	**res;

	if (!strs || !f)
		return (NULL);
	i = 0;
	res = (char **)ft_calloc(ft_strslen(strs) + 1, sizeof(char *));
	if (!res)
		return (NULL);
	while (strs[i] != NULL)
	{
		res[i] = (*f)(strs[i]);
		if (!res[i])
		{
			ft_free_strs(res);
			return (NULL);
		}
		i++;
	}
	return (res);
}
