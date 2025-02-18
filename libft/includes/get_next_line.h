/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 19:22:12 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/15 14:55:07 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define FD_LIMIT 1024

char	*get_next_line(int fd);
char	*get_next_line_fds(int fd);
size_t	check_stash(char *stash);
void	shift_stash(char *stash, int start);
char	*extract_line(char *stash);
char	*strjoin_free(char *str1, char *str2);

#endif
