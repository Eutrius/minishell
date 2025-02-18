/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 12:45:12 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/15 14:54:58 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*get_line(int fd, char **stash, char **line);

char	*get_next_line_fds(int fd)
{
	static char	*stashes[FD_LIMIT];
	char		**stash;
	char		*line;

	if (fd < 0 || fd >= FD_LIMIT || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	stash = &stashes[fd];
	if (!*stash)
	{
		*stash = (char *)ft_calloc(BUFFER_SIZE, 1);
		if (!*stash)
			return (NULL);
	}
	return (get_line(fd, stash, &line));
}

static char	*get_line(int fd, char **stash, char **line)
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
			if (ft_strlen(*line) == 0)
				break ;
			free(*stash);
			*stash = NULL;
			return (*line);
		}
	}
	free(*stash);
	free(*line);
	*stash = NULL;
	return (NULL);
}
