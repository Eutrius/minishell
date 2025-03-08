/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:17:41 by jyriarte          #+#    #+#             */
/*   Updated: 2025/03/04 13:27:22 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

static void	unshift_file(char **files, int *index);
static int	is_wildcard(char *pattern);

char	**expand_wildcard(char *pattern)
{
	char	**files;
	int		i;

	i = 0;
	if (!is_wildcard(pattern))
		return (NULL);
	files = get_files(pattern[0] == '.');
	if (files == NULL)
		return (NULL);
	while (files[i] != NULL)
	{
		if (match_wildcard(pattern, files[i], 0))
			unshift_file(files, &i);
		else
			i++;
	}
	if (ft_strslen(files) == 0)
	{
		free(files);
		files = NULL;
	}
	return (files);
}

static int	is_wildcard(char *pattern)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (pattern[i] != '\0')
	{
		check_quotes(pattern[i], &in_quote);
		if (in_quote == 0 && pattern[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

static void	unshift_file(char **files, int *index)
{
	int	i;

	i = *index;
	free(files[i]);
	while (files[i] != NULL)
	{
		files[i] = files[i + 1];
		i++;
	}
}
