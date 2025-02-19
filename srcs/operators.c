#include "../includes/minishell.h"
#include "libft.h"

int	init_operators(t_data *data)
{
	data->operators = ft_calloc(1, sizeof(t_operators));
	if (data->operators)
		return (0);
	data->operators->pipe = '|';
	data->operators->space = ' ';
	data->operators->redirection_f = '<';
	data->operators->redirection_t = '>';
	data->operators->double_pipe = ft_strdup("||");
	data->operators->op_and = ft_strdup("&&");
	data->operators->append = ft_strdup(">>");
	data->operators->here_doc = ft_strdup("<<");
	return (1);
}
