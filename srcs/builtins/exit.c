/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:34:13 by lonulli           #+#    #+#             */
/*   Updated: 2025/03/07 22:34:13 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	clean_exit(t_data *data, char **args)
{
	int	exit_value;

	exit_value = 0;
	printf("exit\n");
	if (ft_strslen(args) > 2)
	{
		print_error2("bashbros: ", "exit: ", "too many arguments");
		g_status = 255;
		return ;
	}
	if (ft_strslen(args) == 2 && args[1])
	{
		if (!check_exit_value(args[1]))
		{
			print_error3("bashbros: ", "exit: ", args[1],
				" numeric argument required");
			free_memory(data, args);
			exit(2);
		}
	}
	if (args[1])
	{
		exit_value = ft_atoi(args[1]);
		free_memory(data, args);
		exit(exit_value);
	}
	free_memory(data, args);
	exit(0);
}
