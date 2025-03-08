/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:33:50 by lonulli           #+#    #+#             */
/*   Updated: 2025/03/07 22:33:51 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
// clang-format off
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
// clang-format on
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

static char	**ft_strsjoin(char **strs_dest, char **strs_join);
static int	wildcard_is_null(char ***new_args, char **args, int i);

char	**expand_cmd(char **args)
{
	int		i;
	char	**new_args;
	char	**expanded_arg;

	i = 0;
	new_args = ft_calloc(1, sizeof(char *));
	while (new_args && args && args[i])
	{
		expanded_arg = expand_wildcard(args[i]);
		if (expanded_arg == NULL)
		{
			if (!wildcard_is_null(&new_args, args, i))
				return (NULL);
		}
		else
			new_args = ft_strsjoin(new_args, expanded_arg);
		if (!new_args)
		{
			free(new_args);
			return (NULL);
		}
		i++;
	}
	ft_free_strs(args);
	return (new_args);
}

static int	wildcard_is_null(char ***new_args, char **args, int i)
{
	char	*tmp;

	remove_quotes(args[i]);
	tmp = ft_strdup(args[i]);
	if (!tmp)
	{
		ft_free_strs(args);
		ft_free_strs(*new_args);
		return (0);
	}
	*new_args = ft_strscat(*new_args, tmp);
	return (1);
}

char	*expand_files(char *file)
{
	char	**new_files;
	int		num_strings;

	new_files = expand_wildcard(file);
	num_strings = ft_strslen(new_files);
	if (num_strings > 1)
	{
		print_error2("bashbros: ", file, " Ambigous redirect");
		return (NULL);
	}
	else if (num_strings == 1)
		return (new_files[0]);
	else
	{
		remove_quotes(file);
		return (file);
	}
	return (NULL);
}

static char	**ft_strsjoin(char **strs_dest, char **strs_join)
{
	char	**res;
	int		i;
	int		j;

	res = ft_calloc((ft_strslen(strs_dest) + ft_strslen(strs_join) + 1),
			sizeof(char *));
	i = 0;
	j = 0;
	while (res && strs_dest && strs_dest[i])
	{
		res[i] = strs_dest[i];
		i++;
	}
	while (res && strs_join && strs_join[j])
	{
		res[i] = strs_join[j];
		j++;
		i++;
	}
	free(strs_dest);
	free(strs_join);
	return (res);
}
