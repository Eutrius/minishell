/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:05:18 by jyriarte          #+#    #+#             */
/*   Updated: 2025/03/04 11:53:09 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

static int	sub_var(char *str, int *i, int *j, char **res);
static int	sub_status(char *str, int *i, int *j, char **res);
static void	init_vars(int *i, int *j, int *in_quote, char **res);

int	expand_vars(t_parser *parser)
{
	int		i;
	char	*tmp;
	t_token	*curr_token;

	i = 0;
	tmp = NULL;
	while (parser->tokens[i] != NULL)
	{
		curr_token = parser->tokens[i];
		if (curr_token->type & (CMD | FILENAME))
		{
			tmp = expand_var(curr_token->content);
			if (tmp == NULL)
				return (1);
			free(curr_token->content);
			curr_token->content = tmp;
		}
		i++;
	}
	return (0);
}

char	*expand_var(char *str)
{
	int		i;
	int		j;
	int		in_quote;
	char	*res;

	init_vars(&i, &j, &in_quote, &res);
	while (str[i] != '\0')
	{
		if (in_quote != 1 && str[i] == '$')
		{
			if (str[i + 1] == '?')
				sub_status(str, &i, &j, &res);
			else if (str[i + 1] != '\0' && str[i + 1] != '$')
			{
				if (sub_var(str, &i, &j, &res))
					break ;
			}
		}
		check_quotes(str[i], &in_quote);
		i++;
	}
	if (str[j] != '\0')
		res = safe_join(res, &str[j]);
	return (res);
}

static void	init_vars(int *i, int *j, int *in_quote, char **res)
{
	*i = 0;
	*j = 0;
	*in_quote = 0;
	*res = NULL;
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
