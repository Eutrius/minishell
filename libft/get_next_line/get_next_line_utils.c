/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 19:22:05 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/15 14:55:52 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdlib.h>

char	*extract_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	while (i < BUFFER_SIZE && stash[i] != '\0')
	{
		if (stash[i] == '\n')
		{
			line = ft_strndup(stash, i + 1);
			shift_stash(stash, i + 1);
			return (line);
		}
		i++;
	}
	line = ft_strndup(stash, i);
	shift_stash(stash, i);
	return (line);
}

void	shift_stash(char *stash, int start)
{
	size_t	i;

	i = 0;
	while (start < BUFFER_SIZE && stash[start])
	{
		stash[i] = stash[start];
		stash[start] = '\0';
		i++;
		start++;
	}
	while (i < BUFFER_SIZE && stash[i])
	{
		stash[i] = '\0';
		i++;
	}
}

char	*strjoin_free(char *str1, char *str2)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	new_str = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (str1 && str1[i] != '\0')
	{
		new_str[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2 && str2[j] != '\0')
	{
		new_str[i + j] = str2[j];
		j++;
	}
	new_str[i + j] = '\0';
	free(str1);
	free(str2);
	return (new_str);
}

size_t	check_stash(char *stash)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE && stash[i] != '\0')
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
