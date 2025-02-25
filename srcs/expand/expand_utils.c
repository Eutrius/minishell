#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

int	is_valid(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char  *extract_before_dollar(char *ptr)
{
	int i = 0;
	char *prefix_var;
	while(ptr[i] && ptr[i] != '$')
		i++;
	prefix_var = ft_calloc(i + 1,1);
	if (!prefix_var)
	{
		print_error(ERR_MALLOC);
		return NULL;
	}
	i = 0;
	while(ptr[i] && ptr[i] != '$')
	{
		prefix_var[i] = ptr[i];
		i++;
	}
	prefix_var[i] = '\0';
	return prefix_var;
}

char	*extract_var(char *ptr)
{
	int		i;
	int 	j;
	int start = 0;;
	char	*new_var;

	i = 0;
	j = 0;
	while(ptr[i] && ptr[i] != '$')
		i++;
	if (ptr[i] == '$')
	{
		i++;
		start = i;
		while(is_valid(ptr[i]))
			i++;
	}
	new_var = ft_calloc(i - start + 1,1);
	if (!new_var)
	{
		print_error(ERR_MALLOC);
		return NULL;
	}
	i = 0;
	while(ptr[i] && ptr[i] != '$')
		i++;
	if (ptr[i] == '$')
	{
		i++;
		start = i;
		while(ptr[i] && is_valid(ptr[i]))
		{
			new_var[j] = ptr[i];
			i++;
			j++;
		}
		new_var[j] = '\0';
	}
	return new_var;
}

char  *extract_after_dollar(char *ptr)
{
	int i = 0;
	int j = 0;
	char *suffix_var;
	while(ptr[i] && ptr[i] != '$')
		i++;
	if (ptr[i] == '$')
		i++;
	i = 0;
	while(is_valid(ptr[i]))
		i++;
	int start = i;
	while(ptr[i])
		i++;
	suffix_var = ft_calloc(i - start + 1,1);
	if (!suffix_var)
	{
		print_error(ERR_MALLOC);
		return NULL;
	}
	i = 0;
	while(ptr[i] && ptr[i] != '$')
		i++;
	if (ptr[i] == '$')
		i++;
	while(is_valid(ptr[i]))
		i++;
	while(ptr[i])
	{
		suffix_var[j] = ptr[i];
		j++;
		i++;
	}
	suffix_var[j] = '\0';
	return suffix_var;
}

char *safe_join(char *s1, char *s2)
{
	if (!s1 && s2)
		return ft_strdup(s2);
	if (s1 && !s2)
		return ft_strdup(s1);
	return ft_strjoin(s1,s2);
}

int	calculate_var_len(char *str)
{
	int	i;
	int	start;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$')
	{
		start = i;
		i++;
		while (is_valid(str[i]))
			i++;
		return (i - start);
	}
	return (0);
}
