#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*extract_before_dollar(char *ptr)
{
	int		i;
	char	*prefix_var;

	i = 0;
	while (ptr[i] && ptr[i] != '$')
		i++;
	prefix_var = ft_calloc(i + 1, 1);
	if (!prefix_var)
	{
		print_error(ERR_MALLOC);
		return (NULL);
	}
	i = 0;
	while (ptr[i] && ptr[i] != '$')
	{
		prefix_var[i] = ptr[i];
		i++;
	}
	prefix_var[i] = '\0';
	return (prefix_var);
}

char	*extract_var(char *ptr)
{
	int		i;
	int		start;
	char	*new_var;

	start = 0;
	i = 0;
	while (ptr[i] && ptr[i] != '$')
		i++;
	if (ptr[i] == '$')
		start = ++i;
	while (ptr[i] && is_valid(ptr[i]))
		i++;
	new_var = ft_calloc(i - start + 1, 1);
	if (!new_var)
	{
		print_error(ERR_MALLOC);
		return (NULL);
	}
	i = 0;
	while (ptr[start] && is_valid(ptr[start]))
		new_var[i++] = ptr[start++];
	new_var[i] = '\0';
	return (new_var);
}

char	*extract_after_dollar(char *ptr)
{
	int		i;
	char	*suffix_var;
	int		start;

	i = 0;
	while (ptr[i] && ptr[i] != '$')
		i++;
	if (ptr[i] == '$')
		i++;
	while (ptr[i] && is_valid(ptr[i]))
		i++;
	start = i;
	while (ptr[i])
		i++;
	suffix_var = ft_calloc(i - start + 1, 1);
	if (!suffix_var)
	{
		print_error(ERR_MALLOC);
		return (NULL);
	}
	i = 0;
	while (ptr[start])
		suffix_var[i++] = ptr[start++];
	suffix_var[i] = '\0';
	return (suffix_var);
}

char	*safe_join(char *s1, char *s2)
{
	char	*res;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

int	is_valid(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}
