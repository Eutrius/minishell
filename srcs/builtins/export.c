#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static void	export_no_args(t_data *data);
static void	sort_export(char **sorted_exp);
static void	export_with_args(t_data *data, char **args, int not_valid);
static void	append_vars(t_data *data, char **new_env, int i);

void	custom_export(t_data *data, char **args)
{
	int			tokens_count;
	int			i;
	int			not_valid;
	extern char	**environ;

	i = 1;
	not_valid = 0;
	tokens_count = ft_strslen(args);
	if (tokens_count >= 2)
	{
		while (i < tokens_count)
		{
			if (!is_valid_identifier(args[i]))
			{
				printf("bash: export: '%s': not a valid identifier\n", args[i]);
				not_valid++;
			}
			g_status = 255;
			i++;
		}
		export_with_args(data, args, not_valid);
	}
	if (tokens_count == 1)
		export_no_args(data);
	environ = data->env;
}

static void	export_with_args(t_data *data, char **args, int not_valid)
{
	int		tokens_count;
	int		i;
	char	**new_env;
	int		strs;

	strs = 0;
	tokens_count = ft_strslen(args) - 1 - not_valid;
	if (tokens_count <= 0)
		return ;
	i = 0;
	if (data->env)
		strs = ft_strslen(data->env);
	new_env = ft_calloc(strs + tokens_count + 1, sizeof(char *));
	if (!new_env)
		return ;
	while (data->env && data->env[i])
	{
		new_env[i] = data->env[i];
		i++;
	}
	data->env = new_env;
	append_vars(data, args, i);
}

static void	export_no_args(t_data *data)
{
	char	**sorted_exp;
	int		i;

	i = 0;
	sorted_exp = export_strsdup(data->env);
	if (!sorted_exp)
		return ;
	while (sorted_exp[i])
	{
		sorted_exp[i] = ft_strjoin("declare -x ", sorted_exp[i]);
		if (!sorted_exp[i])
		{
			ft_free_strs(sorted_exp);
			return ;
		}
		value_checker(sorted_exp, i);
		i++;
	}
	sort_export(sorted_exp);
	print_string_array(sorted_exp);
	ft_free_strs(sorted_exp);
}

static void	append_vars(t_data *data, char **args, int i)
{
	int		j;
	char	*current_token;
	int		to_sub;

	j = 1;
	while (args[j] != NULL)
	{
		current_token = args[j];
		if (is_valid_identifier(current_token))
		{
			to_sub = check_var_existence(data->env, current_token);
			if (to_sub < 0)
				to_sub = i;
			if (to_sub == i || check_equal(current_token))
				data->env[to_sub] = current_token;
			i++;
		}
		j++;
	}
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
