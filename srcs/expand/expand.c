#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*extract_valid_part(char *pointer);
static char	*extract_var(char *pointer);

void	get_var_value(t_token **token)
{
	char	*value;
	char	*curr;
	char	*var;
	char	*orig;
	char	*valid_part;
	int		i;

	i = 1;
	while (token[i])
	{
		curr = (char *)token[i]->content;
		if (curr[0] == '$')
		{
			orig = ft_strdup(curr);
			valid_part = extract_valid_part(orig);
			var = extract_var(orig);
			value = getenv(var);
			if (value)
			{
				if (valid_part[0] != '\0')
					token[i]->content = ft_strjoin(value, valid_part);
				else
					token[i]->content = ft_strdup(value);
			}
			else
			{
				if (valid_part[0] != '\0')
					token[i]->content = ft_strdup(valid_part);
				else
					token[i]->content = NULL;
			}
			free(var);
			free(orig);
			free(valid_part);
		}
		i++;
	}
}

char	*extract_var(char *pointer)
{
	int		i;
	int		j;
	char	*new_str;

	j = 0;
	i = calculate_var_len(pointer);
	new_str = ft_calloc(i + 1, 1);
	if (!new_str)
		return (NULL);
	if (pointer[0] == '$')
		j++;
	i = 0;
	while (pointer[j])
	{
		if (is_valid(pointer[j]))
		{
			new_str[i] = pointer[j];
			j++;
			i++;
		}
		else
			break ;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*extract_valid_part(char *pointer)
{
	int		var_len;
	int		remaining_part;
	char	*new_str;
	int		i;
	int		j;

	var_len = calculate_var_len(pointer);
	remaining_part = ft_strlen(pointer) - var_len;
	new_str = ft_calloc(remaining_part + 1, 1);
	if (!new_str)
		return (NULL);
	i = var_len;
	j = 0;
	while (pointer[i])
	{
		new_str[j] = pointer[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}
