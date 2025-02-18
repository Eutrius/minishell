#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <string.h>
#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>

int main()
{
	char *buf;
	t_data data;

	while(1)
	{
		buf = readline("B_bros > ");
		add_history(buf);
		if (!ft_strcmp(buf,"exit"))
			exit(0);

		// Parse
		// Execute
	}
	return 0;
}

