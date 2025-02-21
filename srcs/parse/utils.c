/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:33:10 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/20 17:35:19 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

t_token	*create_token(void *content, t_type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = content;
	token->type = type;
	return (token);
}

int	is_special(int c)
{
	if (c == ' ')
		return (1);
	else if (c == '|')
		return (1);
	else if (c == '&')
		return (1);
	else if (c == '<')
		return (1);
	else if (c == '>')
		return (1);
	else if (is_quote(c))
		return (1);
	else if (is_dquote(c))
		return (1);
	else if (c == '(')
		return (1);
	else if (c == ')')
		return (1);
	return (0);
}

int	is_quote(int c)
{
	if (c == '\'')
		return (1);
	return (0);
}

int	is_dquote(int c)
{
	if (c == '"')
		return (1);
	return (0);
}

void	parse_strs_error(char ***strs, char *msg)
{
	ft_free_strs(*strs);
	*strs = NULL;
	print_error(msg);
}

void	print_error(char *msg)
{
	ft_putstr_fd(msg, 2);
}

void	print_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		printf("content: %s, %s\n", (char *)tokens[i]->content,
			get_enum(tokens[i]->type));
		i++;
	}
}

char	*get_enum(t_type type)
{
	if (type == NAME)
		return ("NAME");
	if (type == CMD)
		return ("CMD");
	if (type == FLAG)
		return ("FLAG");
	if (type == WILDCARD)
		return ("WILDCARD");
	return ("OTHERS");
}

t_token	*assign_token(t_token **tokens, char *str, int index)
{
	if (str[0] == '-' && ft_strlen(str) != 0)
		return (create_token(str, FLAG));
	else if (str[0] == '*')
		return (create_token(str, WILDCARD));
	else if (str[0] == '$')
		return (create_token(str, VARIABLE));
	else if (!ft_strcmp(str, ";"))
		return (create_token(str, OPERATOR));
	else if (!ft_strcmp(str, "|"))
		return (create_token(str, OPERATOR));
	else if (!ft_strcmp(str, "&&"))
		return (create_token(str, OPERATOR));
	else if (!ft_strcmp(str, "||"))
		return (create_token(str, OPERATOR));
	else if (index == 0)
		return (create_token(str, CMD));
	else if (index != 0 && !ft_strcmp(tokens[index - 1]->content, ";"))
		return (create_token(str, CMD));
	else if (index != 0 && !ft_strcmp(tokens[index - 1]->content, "|"))
		return (create_token(str, CMD));
	else if (index != 0 && !ft_strcmp(tokens[index - 1]->content, "&&"))
		return (create_token(str, CMD));
	else
		return (create_token(str, NAME));
}
