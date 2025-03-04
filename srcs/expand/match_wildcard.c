/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:17:33 by jyriarte          #+#    #+#             */
/*   Updated: 2025/03/04 11:17:34 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	skip_multi_ast(char *pattern, int *i);
static int	recurse_rest(char *pattern, char *filename, int *j, int in_quote);

int	match_wildcard(char *pattern, char *filename, int in_quote)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (pattern[i] == '\0')
		return (!(filename[j] == '\0'));
	if (check_quotes(pattern[i], &in_quote))
		return (match_wildcard(&pattern[i + 1], &filename[j], in_quote));
	if (pattern[i] == '*' && in_quote == 0)
	{
		if (!skip_multi_ast(pattern, &i))
			return (0);
		recurse_rest(&pattern[i + 1], filename, &j, in_quote);
		return (match_wildcard(&pattern[i + 1], &filename[j], in_quote));
	}
	if (pattern[i] == filename[j])
	{
		if (filename[j] != '\0')
			return (match_wildcard(&pattern[i + 1], &filename[j + 1],
					in_quote));
	}
	return (1);
}

static int	skip_multi_ast(char *pattern, int *i)
{
	while (pattern[*i + 1] == '*')
		(*i)++;
	if (pattern[*i + 1] == '\0')
		return (0);
	return (1);
}

static int	recurse_rest(char *pattern, char *filename, int *j, int in_quote)
{
	while (filename[*j] != '\0')
	{
		if (match_wildcard(pattern, &filename[*j], in_quote) == 0)
			return (0);
		(*j)++;
	}
	return (1);
}
