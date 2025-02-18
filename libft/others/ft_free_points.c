/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_points.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:55:33 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/27 17:56:21 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_free_points(t_point **points)
{
	size_t	i;

	i = 0;
	while (points && points[i] != NULL)
	{
		free(points[i]);
		i++;
	}
	free(points);
}
