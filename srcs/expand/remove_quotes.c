/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:10:45 by jyriarte          #+#    #+#             */
/*   Updated: 2025/03/03 11:18:54 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void	shift_str(char *str, int *index, int (*f)(int));

void	remove_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_quote(str[i]))
			shift_str(str, &i, is_quote);
		else if (is_dquote(str[i]))
			shift_str(str, &i, is_dquote);
		i++;
	}
}

static void	shift_str(char *str, int *index, int (*ctrl)(int))
{
	int	j;
	int	len;

	len = ft_strlen(str);
	j = *index + 1;
	while (!ctrl(str[j]))
		j++;
	ft_strlcpy(&str[j], &str[j + 1], len);
	ft_strlcpy(&str[*index], &str[*index + 1], len);
	*index = j - 2;
}
