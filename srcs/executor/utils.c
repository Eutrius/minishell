#include "libft.h"
#include "minishell.h"
// clang-format off
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
// clang-format on
#include <unistd.h>

char	**get_args(char *av)
{
	char	**args;

	if (!av)
		return (NULL);
	args = ft_split(av, ' ');
	if (!args)
	{
		ft_free_strs(args);
		print_error(ERR_MALLOC);
		return (NULL);
	}
	return (args);
}
