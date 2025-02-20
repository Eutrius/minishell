/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:01:15 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/20 17:58:25 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>

static void	extract_name(char ***strs, char *str, int *index, int *skipped);
static void	extract_dquote(char ***strs, char *str, int *index, int *skipped);
static void	extract_quote(char ***strs, char *str, int *index, int *skipped);
static int	skip_space(char *str, int *index, int *skipped);

char	**split_cmd(t_data *data)
{
	char	**strs;
	int		skipped;
	int		i;

	strs = ft_calloc(1, sizeof(char *));
	if (strs == NULL)
		parse_strs_error(&strs, ERR_MALLOC);
	i = 0;
	skipped = 1;
	while (strs && data->buffer[i] != '\0')
	{
		if (skip_space(data->buffer, &i, &skipped))
			continue ;
		if (data->buffer[i] == '"')
			extract_dquote(&strs, data->buffer, &i, &skipped);
		else if (data->buffer[i] == '\'')
			extract_quote(&strs, data->buffer, &i, &skipped);
		else if (is_special(data->buffer[i]))
			extract_op(&strs, data->buffer, &i, &skipped);
		else
			extract_name(&strs, data->buffer, &i, &skipped);
	}
	return (strs);
}

static int	skip_space(char *str, int *index, int *skipped)
{
	if (str[*index] == ' ')
	{
		(*index)++;
		*skipped = 1;
		return (1);
	}
	return (0);
}

static void	extract_name(char ***strs, char *str, int *index, int *skipped)
{
	int		i;
	char	*tmp;

	i = *index;
	while (str[i] != '\0' && !is_special(str[i]))
		i++;
	tmp = ft_strndup(&str[*index], i - *index);
	if (tmp == NULL)
		return (parse_strs_error(strs, ERR_MALLOC));
	if (!(*skipped))
		join_last(strs, tmp);
	else
		*strs = ft_strscat(*strs, tmp);
	if (*strs == NULL)
		print_error(ERR_MALLOC);
	*skipped = 0;
	*index = i;
}

static void	extract_quote(char ***strs, char *str, int *index, int *skipped)
{
	int		i;
	char	*tmp;

	(*index)++;
	i = *index;
	while (str[i] != '\0' && str[i] != '\'')
		i++;
	if (str[i] == '\0')
		return (parse_strs_error(strs, ERR_SYNTAX));
	tmp = ft_strndup(&str[*index], i - *index);
	if (!tmp)
		return (parse_strs_error(strs, ERR_MALLOC));
	if (!(*skipped))
		join_last(strs, tmp);
	else
		*strs = ft_strscat(*strs, tmp);
	if (*strs == NULL)
		print_error(ERR_MALLOC);
	*skipped = 0;
	*index = i + 1;
}

static void	extract_dquote(char ***strs, char *str, int *index, int *skipped)
{
	int		i;
	char	*tmp;

	(*index)++;
	i = *index;
	while (str[i] != '\0' && str[i] != '"')
		i++;
	if (str[i] == '\0')
		return (parse_strs_error(strs, ERR_SYNTAX));
	tmp = ft_strndup(&str[*index], i - *index);
	if (!tmp)
		return (parse_strs_error(strs, ERR_MALLOC));
	if (!(*skipped))
		join_last(strs, tmp);
	else
		*strs = ft_strscat(*strs, tmp);
	if (*strs == NULL)
		print_error(ERR_MALLOC);
	*skipped = 0;
	*index = i + 1;
}
