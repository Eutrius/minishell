#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	free_previous_sorted_exp(char **exported_dup, int i);
static void	export(t_data *data);
static void	sort_export(char **sorted_exp);
static void	append_env_variable(t_data *data);

void	custom_export(t_data *data)
{
	int		tokens_count;
	char	*name;

	tokens_count = count_tokens(data->cmd_line);
	if (data->cmd_line[1])
	{
		name = (char *)data->cmd_line[1]->content;
		if (!is_valid_identifier(name))
		{
			printf("bash: export: '%s': not a valid identifier\n", name);
			g_status = 255;
			return ;
		}
	}
	if (tokens_count == 1)
		export(data);
	if (tokens_count >= 2)
		append_env_variable(data);
}

static void	append_env_variable(t_data *data)
{
	int		token_counts;
	int		i;
	int		j;
	char	**new_env;
	int		strs;

	token_counts = count_tokens(data->cmd_line) - 1;
	i = 0;
	j = 1;
	strs = strs_count(data->env);
	new_env = ft_calloc(strs + token_counts + 1, sizeof(char *));
	if (!new_env)
		return ;
	while (data->env[i])
	{
		new_env[i] = ft_strdup(data->env[i]);
		free(data->env[i]);
		i++;
	}
	while (token_counts)
	{
		new_env[i] = ft_strdup(data->cmd_line[j++]->content);
		if (!new_env[i++])
			ft_free_strs(new_env);
		token_counts--;
	}
	free(data->env);
	new_env[i] = NULL;
	data->env = new_env;
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
		if (ft_strchr(sorted_exp[i], '=') 
      && sorted_exp[i][find_eq_i(sorted_exp[i])])
		{
			tmp = sorted_exp[i];
			sorted_exp[i] = ft_strjoin(sorted_exp[i], "\"\"");
			free(tmp);
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
