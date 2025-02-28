/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:05:18 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/28 23:20:24 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

static void	check_quotes(char *str, int *i, int *in_quote);
static int	sub_var(char *str, int *i, int *j, char **res);
static int	sub_status(char *str, int *i, int *j, char **res);

char	*expand_var(char *str)
{
	int		i;
	int		j;
	int		in_quote;
	char	*res;

	i = 0;
	j = 0;
	in_quote = 0;
	res = NULL;
	while (str[i] != '\0')
	{
		if (in_quote != 1 && str[i] == '$')
		{
			if (str[i + 1] == '?')
				sub_status(str, &i, &j, &res);
			else if (is_valid(str[i + 1]))
				sub_var(str, &i, &j, &res);
			if (res == NULL)
				return (NULL);
		}
		check_quotes(str, &i, &in_quote);
	}
	if (str[j] != '\0')
		res = safe_join(res, &str[j]);
	return (res);
}

static int	sub_var(char *str, int *i, int *j, char **res)
{
	char	tmp;

	str[*i] = '\0';
	*res = safe_join(*res, &str[*j]);
	if (*res == NULL)
		return (print_error(ERR_MALLOC));
	(*i)++;
	*j = *i;
	while (str[*i] && is_valid(str[*i]))
		(*i)++;
	tmp = str[*i];
	str[*i] = '\0';
	*res = safe_join(*res, getenv(&str[*j]));
	if (*res == NULL)
		return (print_error(ERR_MALLOC));
	str[*i] = tmp;
	*j = *i;
	(*i)--;
	return (0);
}

static int	sub_status(char *str, int *i, int *j, char **res)
{
	char	*status;

	str[*i] = '\0';
	*res = safe_join(*res, &str[*j]);
	if (*res == NULL)
		return (print_error(ERR_MALLOC));
	*i += 2;
	*j = *i;
	status = ft_itoa(g_status);
	if (status == NULL)
	{
		free(*res);
		return (print_error(ERR_MALLOC));
	}
	*res = safe_join(*res, status);
	if (*res == NULL)
	{
		free(status);
		return (print_error(ERR_MALLOC));
	}
	free(status);
	return (0);
}

static void	check_quotes(char *str, int *i, int *in_quote)
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
