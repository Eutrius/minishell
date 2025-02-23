/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:10:22 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/23 11:43:07 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

char	*if_double(char *str, int *index, char *twice, char *once)
{
	if (!ft_strncmp(&str[*index], twice, 2))
	{
		(*index)++;
		return (ft_strdup(twice));
	}
	else
		return (ft_strdup(once));
}

void	join_last(t_parser *parser)
{
	char	*new_content;
	char	*old_content;

	old_content = parser->token->content;
	new_content = ft_strjoin(old_content, parser->str);
	if (new_content == NULL)
	{
		print_error(ERR_MALLOC);
		return (parse_error(parser));
	}
	parser->token->content = new_content;
	free(old_content);
	free(parser->str);
	parser->str = NULL;
}
