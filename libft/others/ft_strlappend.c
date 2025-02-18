/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlappend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:48:52 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/15 14:10:33 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_strlappend(char *str, int c, size_t size)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && i < size - 2)
		i++;
	if (i < size - 2)
	{
		str[i] = c;
		str[i + 1] = '\0';
	}
}
