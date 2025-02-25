#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// static char	*extract_valid_part(char *pointer);
static char *create_var(char *ptr);

void	check_value(t_data *data)
{
	int		i;
	t_token	**cmd_line;

	i = 1;
	cmd_line = data->cmd_line;
	while (cmd_line[i])
	{
		if (cmd_line[i]->type == NAME)
			cmd_line[i]->content = create_var(cmd_line[i]->content);
		i++;
	}
}

static char *create_var(char *ptr)
{
	char *before_dollar;
	char *var;
	char *var2;
	char *after_var;
	char *tmp;
	char *final_string;
	before_dollar = extract_before_dollar(ptr);
	var = extract_var(ptr);
	var2 = getenv(var);
	after_var = extract_after_dollar(ptr);
	tmp = safe_join(before_dollar,var2);
	if (!tmp)
	{
		print_error(ERR_MALLOC);
		return NULL;
	}
	final_string = safe_join(tmp,after_var);
	if (!final_string)
	{
		print_error(ERR_MALLOC);
		return NULL;
	}
	free(before_dollar);
	free(var);
	free(after_var);
	return final_string;
}

