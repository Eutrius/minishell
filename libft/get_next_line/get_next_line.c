/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 19:22:02 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/15 14:55:35 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*get_line(int fd, char (*stash)[BUFFER_SIZE], char **line);

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	return (get_line(fd, &stash, &line));
}

static char	*get_line(int fd, char (*stash)[BUFFER_SIZE], char **line)
{
	int	bytes_read;

	while (1)
	{
		if (check_stash(*stash))
			return (strjoin_free(*line, extract_line(*stash)));
		*line = strjoin_free(*line, extract_line(*stash));
		if (!line)
			return (NULL);
		bytes_read = read(fd, *stash, BUFFER_SIZE);
		if (bytes_read < 0)
			break ;
		if (bytes_read == 0)
		{
			if (ft_strlen(*line) > 0)
				return (*line);
			break ;
		}
	}
	free(*line);
	return (NULL);
}
