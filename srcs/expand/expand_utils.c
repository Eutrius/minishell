/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:05:18 by jyriarte          #+#    #+#             */
/*   Updated: 2025/03/03 22:19:19 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <dirent.h>
#include <stdlib.h>

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

int	check_quotes(int c, int *in_quote)
{
	if (*in_quote == 0 && is_dquote(c))
		*in_quote = 2;
	else if (*in_quote == 2 && is_dquote(c))
		*in_quote = 0;
	else if (*in_quote == 0 && is_quote(c))
		*in_quote = 1;
	else if (*in_quote == 1 && is_quote(c))
		*in_quote = 0;
	else
		return (0);
	return (1);
}
