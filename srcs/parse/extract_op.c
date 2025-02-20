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

static char	*extract(char *str, int *index, char *twice, char *once);

void	extract_op(char ***strs, char *str, int *index, int *skipped)
{
	char	*tmp;

	if (str[*index] == '|')
		tmp = extract(str, index, "||", "|");
	else if (str[*index] == '(')
		tmp = ft_strdup("(");
	else if (str[*index] == ')')
		tmp = ft_strdup(")");
	else if (str[*index] == '>')
		tmp = extract(str, index, ">>", ">");
	else if (str[*index] == '<')
		tmp = extract(str, index, "<<", "<");
	else
		tmp = extract(str, index, "&&", "&");
	if (!tmp)
		return (parse_strs_error(strs, ERR_MALLOC));
	(*index)++;
	*skipped = 1;
	*strs = ft_strscat(*strs, tmp);
	if (!(*strs))
		print_error(ERR_MALLOC);
}

static char	*extract(char *str, int *index, char *twice, char *once)
{
	if (!ft_strncmp(&str[*index], twice, 2))
	{
		(*index)++;
		return (ft_strdup(twice));
	}
	else
		return (ft_strdup(once));
}
