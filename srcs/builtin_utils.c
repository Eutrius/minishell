#include "../libft/libft.h"
#include <unistd.h>

int	is_builtin(char *buf)
{
	if (!ft_strcmp(buf, "echo"))
		return (1);
	if (!ft_strcmp(buf, "cd"))
		return (1);
	if (!ft_strcmp(buf, "pwd"))
		return (1);
	if (!ft_strcmp(buf, "export"))
		return (1);
	if (!ft_strcmp(buf, "unset"))
		return (1);
	if (!ft_strcmp(buf, "env"))
		return (1);
	if (!ft_strcmp(buf, "exit"))
		return (1);
	return (0);
}
