/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:44:13 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/15 14:44:34 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

char	*ft_strndup(char *str, size_t nmemb)
{
	char	*duplicate;
	size_t	i;

	i = 0;
	duplicate = malloc(nmemb + 1);
	if (!duplicate)
		return (NULL);
	while (i < nmemb)
	{
		duplicate[i] = str[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}
