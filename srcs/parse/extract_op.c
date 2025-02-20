/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:55:33 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/20 17:34:57 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

static char	*extract_pipe(char *str, int *index);
static char	*extract_less(char *str, int *index);
static char	*extract_more(char *str, int *index);
static char	*extract_and(char *str, int *index);

void	extract_op(char ***strs, char *str, int *index, int *skipped)
{
	char	*tmp;

	if (str[*index] == '|')
		tmp = extract_pipe(str, index);
	else if (str[*index] == '>')
		tmp = extract_more(str, index);
	else if (str[*index] == '<')
		tmp = extract_less(str, index);
	else
		tmp = extract_and(str, index);
	if (!tmp)
		return (parse_strs_error(strs, ERR_MALLOC));
	(*index)++;
	*skipped = 1;
	*strs = ft_strscat(*strs, tmp);
	if (!(*strs))
		print_error(ERR_MALLOC);
}

static char	*extract_pipe(char *str, int *index)
{
	if (!ft_strcmp(&str[*index], "||"))
	{
		(*index)++;
		return (ft_strdup("||"));
	}
	else
		return (ft_strdup("|"));
}

static char	*extract_and(char *str, int *index)
{
	if (!ft_strcmp(&str[*index], "&&"))
	{
		(*index)++;
		return (ft_strdup("&&"));
	}
	else
		return (ft_strdup("&"));
}

static char	*extract_less(char *str, int *index)
{
	if (!ft_strcmp(&str[*index], "<<"))
	{
		(*index)++;
		return (ft_strdup("<<"));
	}
	else
		return (ft_strdup("<"));
}

static char	*extract_more(char *str, int *index)
{
	if (!ft_strcmp(&str[*index], ">>"))
	{
		(*index)++;
		return (ft_strdup(">>"));
	}
	else
		return (ft_strdup(">"));
}
