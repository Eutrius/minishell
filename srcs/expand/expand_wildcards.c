/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:19:15 by jyriarte          #+#    #+#             */
/*   Updated: 2025/03/03 12:24:24 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*static int	is_file_valid(char *pattern, char *str);*/

/*char	**expand_wildcards(char *str, char **files)*/
/*{*/
/*}*/

static int	is_file_valid(char *pattern, char *filename)
{
	int	i;
	int	j;
	int	in_quote;

	i = 0;
	j = 0;
	in_quote = 0;
	while (1)
	{
		if (pattern[i] == '\0' && filename[j] == '\0')
			return (0);
		else if (pattern[i] == filename[j])
		{
			j++;
			i++;
			continue ;
		}
		if (in_quote == 0 && is_dquote(pattern[i]))
			in_quote = 2;
		else if (in_quote == 2 && is_dquote(pattern[i]))
			in_quote = 0;
		else if (in_quote == 0 && is_quote(pattern[i]))
			in_quote = 1;
		else if (in_quote == 1 && is_quote(pattern[i]))
			in_quote = 0;
		while (in_quote == 0 && pattern[i] == '*' && pattern[i + 1] == '*')
			i++;
		if ((pattern[i] == '*' && pattern[i + 1] == '\0') && filename[j])
			j++;
		else if (filename[j] == '\0')
			return (pattern[i] == '*');
	}
	return (0);
}

/*static int	is_file_valid(char *pattern, char *str)*/
/*{*/
/*	if (pattern[0] == '\0' && str[0] == '\0')*/
/*		return (1);*/
/*	if (ft_strcmp("*", pattern))*/
/*		return (1);*/
/*	if (pattern[0] == '*')*/
/*		return (is_file_valid(&pattern[1], str) || (str[1] != '\0'*/
/*				&& is_file_valid(pattern, &str[1])));*/
/*	if (pattern[0] == str[0])*/
/*		return (str[0] != '\0' && is_file_valid(&pattern[1], &str[1]));*/
/*	return (0);*/
/*}*/
