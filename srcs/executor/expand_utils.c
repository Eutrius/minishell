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

char	**expand_cmd(char **args)
{
	int		i;
	char	**new_args;
	char	**expanded_arg;
	char	*tmp;

	i = 0;
	new_args = ft_calloc(1, sizeof(char *));
	while (args[i])
	{
		expanded_arg = expand_wildcard(args[i]);
		if (expanded_arg == NULL)
		{
			remove_quotes(args[i]);
			tmp = ft_strdup(args[i]);
			if (!tmp)
			{
				ft_free_strs(args);
				ft_free_strs(new_args);
				return (NULL);
			}
			new_args = ft_strscat(new_args, tmp);
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
	int		strs_dest_len;
	int		strs_join_len;
	char	**res;
	int		i;
	int		j;

	strs_dest_len = ft_strslen(strs_dest);
	strs_join_len = ft_strslen(strs_join);
	res = ft_calloc((strs_dest_len + strs_join_len + 1), sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (strs_dest && strs_dest[i])
	{
		res[i] = strs_dest[i];
		i++;
	}
	while (strs_join && strs_join[j])
	{
		res[i] = strs_join[j];
		j++;
		i++;
	}
	free(strs_dest);
	free(strs_join);
	return (res);
}
