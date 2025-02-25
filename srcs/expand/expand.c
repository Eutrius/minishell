#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// static char	*extract_valid_part(char *pointer);
static char	*extract_var(char *pointer);

void	check_value(t_data *data)
{
	int		i;
	char	*var;
	t_token	**cmd_line;
	char	*value;

	i = 1;
	cmd_line = data->cmd_line;
	while (cmd_line[i])
	{
		var = extract_var(cmd_line[i]->content);
		if (!var)
			return ;
		value = getenv(var);
		if (value)
			cmd_line[i]->content = ft_strdup(value);
		else
			cmd_line[i]->content = NULL;
		i++;
	}
	free(var);
}

char	*extract_var(char *ptr)
{
	int		i;
	int		j;
	char	*new_var;

	j = 0;
	i = 0;
	new_var = ft_calloc(i + 1, 1);
	if (!new_var)
		return (NULL);
	i = 0;
	while (ptr[j] && ptr[j] != '$')
	{
		new_var[i] = ptr[j];
		j++;
	}
	if (ptr[j] == '$')
	{
		j++;
		while (is_valid(ptr[j]))
		{
			new_var[i] = ptr[j];
			i++;
			j++;
		}
		new_var[i] = '\0';
	}
	return (new_var);
}

// char	*extract_valid_part(char *pointer)
// {
// 	int		var_len;
// 	int		remaining_part;
// 	char	*new_str;
// 	int		i;
// 	int		j;

// 	var_len = calculate_var_len(pointer);
// 	remaining_part = ft_strlen(pointer) - var_len;
// 	new_str = ft_calloc(remaining_part + 1, 1);
// 	if (!new_str)
// 		return (NULL);
// 	i = var_len;
// 	j = 0;
// 	while (pointer[i])
// 	{
// 		new_str[j] = pointer[i];
// 		i++;
// 		j++;
// 	}
// 	new_str[j] = '\0';
// 	return (new_str);
// }
