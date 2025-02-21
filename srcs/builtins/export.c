#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static void	free_previous_sorted_exp(char **exported_dup, int i);
static void	export(t_data *data);
static void	sort_export(char **sorted_exp);
static void	append_env_variable(t_data *data);

void	custom_export(t_data *data)
{
	int	tokens_count;
	int	is_export;

	is_export = ft_strcmp(data->cmd_line[0]->content, "export");
	if (!is_export)
	{
		tokens_count = count_tokens(data->cmd_line);
		if (tokens_count == 1)
			export(data);
		if (tokens_count == 2)
			append_env_variable(data);
	}
}

static void	append_env_variable(t_data *data)
{
	int		i;
	int		j;
	char	*str_to_join;
	char	**env;

	i = 0;
	j = -1;
	str_to_join = ft_strdup((char *)data->cmd_line[1]->content);
	if (!str_to_join)
		return ;
	while (data->env[i])
		i++;
	env = ft_calloc(i + 2, sizeof(char *));
	if (!env)
	{
		free(str_to_join);
		return ;
	}
	while (++j < i)
		env[j] = data->env[j];
	env[i] = str_to_join;
	env[i + 1] = NULL;
	free(data->env);
	data->env = env;
}

void	export(t_data *data)
{
	char	**sorted_exp;
	char	*tmp;
	int		i;

	i = 0;
	sorted_exp = ft_strsdup(data->env);
	if (!sorted_exp)
		return ;
	while (sorted_exp[i])
	{
		tmp = sorted_exp[i];
		sorted_exp[i] = ft_strjoin("declare -x ", sorted_exp[i]);
		free(tmp);
		if (!sorted_exp[i])
		{
			free_previous_sorted_exp(sorted_exp, i);
			return ;
		}
		i++;
	}
	sort_export(sorted_exp);
	print_string_array(sorted_exp);
	ft_free_strs(sorted_exp);
}

static void	sort_export(char **sorted_exp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (sorted_exp[i])
	{
		j = i + 1;
		while (sorted_exp[j])
		{
			if (ft_strcmp(sorted_exp[i], sorted_exp[j]) > 0)
			{
				tmp = sorted_exp[i];
				sorted_exp[i] = sorted_exp[j];
				sorted_exp[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	free_previous_sorted_exp(char **exported_dup, int i)
{
	while (i)
	{
		free(exported_dup[i]);
		i--;
	}
	free(exported_dup);
}
