/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:34:02 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/20 12:10:15 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_free_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs && strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
