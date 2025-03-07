#include "libft.h"
#include "minishell.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	free_memory(t_data *data, char **args)
{
	if (data->env)
		ft_free_strs(data->env);
	if (args)
		ft_free_strs(args);
	if (data->tokens)
		free_tokens(data->tokens);
}
