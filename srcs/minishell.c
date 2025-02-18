/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:03:18 by lonulli           #+#    #+#             */
/*   Updated: 2025/02/18 14:04:08 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char	*buf;
	t_data	data;

	(void)data;
	while (1)
	{
		buf = readline("B_bros > ");
		add_history(buf);
		if (!ft_strcmp(buf, "exit"))
			exit(0);
		data.cmd = parse_cmd(buf);
		print_tokens(data.cmd);
		free(buf);
	}
	return (0);
}
