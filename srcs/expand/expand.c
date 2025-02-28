#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// static char	*extract_valid_part(char *pointer);
static char	*create_var(char *ptr);
void		check_quotes(int *in_quote, int c);

char	*expand_var(char *str)
{
	int		i;
	int		in_quote;
	char	*res;
	char	*pre;
	int		j;
	char	tmp;
	char	*var;

	i = 0;
	j = 0;
	in_quote = 0;
	res = NULL;
	while (str[i] != '\0')
	{
		check_quotes(&in_quote, str[i]);
		if (in_quote != 1 && str[i] == '$')
		{
			pre = ft_strndup(&str[j], i);
			printf("%s\n", pre);
			res = safe_join(res, pre);
			i++;
			j = i;
			while (str[i] && is_valid(str[i]))
				i++;
			tmp = str[i];
			str[i] = '\0';
			var = getenv(&str[j]);
			res = safe_join(res, var);
			str[i] = tmp;
			i = j;
			continue ;
		}
		i++;
	}
	if (str[j] != '\0')
		res = safe_join(res, &str[j]);
	free(str);
	return (res);
}

void	check_quotes(int *in_quote, int c)
{
	if (*in_quote == 0 && is_dquote(c))
		*in_quote = 2;
	else if (*in_quote == 2 && is_dquote(c))
		*in_quote = 0;
	else if (*in_quote == 0 && is_quote(c))
		*in_quote = 1;
	else if (*in_quote == 1 && is_quote(c))
		*in_quote = 0;
}

void	check_value(t_data *data)
{
	int		i;
	t_token	**cmd_line;
	void	*tmp;

	i = 1;
	cmd_line = data->cmd_line;
	if (!cmd_line[1])
		return ;
	while (cmd_line[i])
	{
		if (cmd_line[i]->type == NAME)
		{
			tmp = cmd_line[i]->content;
			cmd_line[i]->content = create_var(cmd_line[i]->content);
			free(tmp);
		}
		i++;
	}
}

static char	*create_var(char *ptr)
{
	char	*before_dollar;
	char	*var;
	char	*var2;
	char	*after_var;
	char	*tmp;
	char	*final_string;

	before_dollar = extract_before_dollar(ptr);
	var = extract_var(ptr);
	var2 = getenv(var);
	after_var = extract_after_dollar(ptr);
	tmp = safe_join(before_dollar, var2);
	if (!tmp)
	{
		print_error(ERR_MALLOC);
		return (NULL);
	}
	final_string = safe_join(tmp, after_var);
	if (!final_string)
	{
		print_error(ERR_MALLOC);
		return (NULL);
	}
	free(before_dollar);
	free(var);
	free(after_var);
	return (final_string);
}
