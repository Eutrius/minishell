/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointscat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:46:10 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/27 18:02:38 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_point	**ft_pointscat(t_point **points, t_point *point)
{
	t_point	**res;
	int		len;
	int		i;

	len = 0;
	while (points[len] != NULL)
		len++;
	res = ft_calloc(len + 2, sizeof(t_point *));
	if (!res)
	{
		ft_free_points(points);
		return (NULL);
	}
	i = 0;
	while (points[i] != NULL)
	{
		res[i] = points[i];
		i++;
	}
	res[i] = point;
	free(points);
	return (res);
}
