#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	export_no_args(t_data *data);
static void	sort_export(char **sorted_exp);
static void	export_with_args(t_data *data, int not_valid);
static void	append_vars(t_data *data, char **new_env, int i);

void	custom_export(t_data *data)
{
	int		tokens_count;
	char	*name;
	int		i;
	int		not_valid;

	i = 1;
	not_valid = 0;
	tokens_count = count_tokens(data->cmd_line);
	if (tokens_count >= 2)
	{
		while (i < tokens_count)
		{
			name = (char *)data->cmd_line[i]->content;
			if (!is_valid_identifier(name))
			{
				printf("bash: export: '%s': not a valid identifier\n", name);
				not_valid++;
			}
			g_status = 255;
			i++;
		}
		export_with_args(data, not_valid);
	}
	if (tokens_count == 1)
		export_no_args(data);
}

static void	export_no_args(t_data *data)
{
	char	**sorted_exp;
	char	*tmp;
	int		i;

	i = 0;
	sorted_exp = export_strsdup(data->env);
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
		value_checker(sorted_exp, i);
		i++;
	}
	sort_export(sorted_exp);
	print_string_array(sorted_exp);
	ft_free_strs(sorted_exp);
}

static void	export_with_args(t_data *data, int not_valid)
{
	int		tokens_count;
	int		i;
	char	**new_env;
	int		strs;

	tokens_count = count_tokens(data->cmd_line) - 1 - not_valid;
	i = 0;
	strs = strs_count(data->env);
	new_env = ft_calloc(strs + tokens_count + 1, sizeof(char *));
	if (!new_env)
		return ;
	while (data->env[i])
	{
		new_env[i] = ft_strdup(data->env[i]);
		free(data->env[i]);
		i++;
	}
	append_vars(data, new_env, i);
}

static void	append_vars(t_data *data, char **new_env, int i)
{
	int	j;
	int	token_count;

	j = 1;
	token_count = count_tokens(data->cmd_line) - 1;
	while (token_count)
	{
		if (!is_valid_identifier(data->cmd_line[j]->content))
		{
			token_count--;
			j++;
			continue ;
		}
		new_env[i] = ft_strdup(data->cmd_line[j]->content);
		if (!new_env[i])
			ft_free_strs(new_env);
		j++;
		i++;
		token_count--;
	}
	free(data->env);
	new_env[i] = NULL;
	data->env = new_env;
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
