/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:30:35 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/20 17:50:53 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

void	parse_cmd(t_data *data)
{
	char	**strs;
	int		i;

	strs = split_cmd(data);
	if (!strs)
		return ;
	i = 0;
	while (strs[i] != NULL)
	{
		printf("%s\n", strs[i]);
		i++;
	}
	free(data->buffer);
}

void	join_last(char ***strs, char *str)
{
	int		len;
	char	*last_str;

	len = ft_strslen(*strs);
	last_str = *strs[len - 1];
	*strs[len - 1] = ft_strjoin(last_str, str);
	if (!(*strs[len - 1]))
		parse_strs_error(strs, ERR_MALLOC);
	free(last_str);
	free(str);
}
