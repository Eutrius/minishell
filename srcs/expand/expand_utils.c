/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:05:18 by jyriarte          #+#    #+#             */
/*   Updated: 2025/03/03 11:20:41 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int	check_entry(struct dirent *entry, char ***res);

char	*safe_join(char *s1, char *s2)
{
	char	*res;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return ((s1));
	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

int	is_valid(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

void	check_quotes(char *str, int *i, int *in_quote)
{
	if (*in_quote == 0 && is_dquote(str[*i]))
		*in_quote = 2;
	else if (*in_quote == 2 && is_dquote(str[*i]))
		*in_quote = 0;
	else if (*in_quote == 0 && is_quote(str[*i]))
		*in_quote = 1;
	else if (*in_quote == 1 && is_quote(str[*i]))
		*in_quote = 0;
	(*i)++;
}

char	**get_files(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**res;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("b_bros: opendir:");
		return (NULL);
	}
	res = ft_calloc(1, sizeof(char *));
	if (res == NULL)
		print_error(ERR_MALLOC);
	while (res != NULL)
	{
		entry = readdir(dir);
		if (check_entry(entry, &res))
			break ;
	}
	closedir(dir);
	return (res);
}

static int	check_entry(struct dirent *entry, char ***res)
{
	if (entry == NULL)
	{
		if (errno != 0)
			perror("b_bros: readdir:");
		else
			return (1);
	}
	else
	{
		*res = ft_strscat(*res, entry->d_name);
		if (*res == NULL)
			print_error(ERR_MALLOC);
	}
	return (0);
}
