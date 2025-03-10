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

static void	print_error_and_free(t_data *data, char **args);

void	clean_exit(t_data *data, char **args)
{
	int	exit_value;

	exit_value = 0;
	printf("exit\n");
	if (ft_strslen(args) > 2)
	{
		print_error2("bashbros: ", "exit: ", "too many arguments", 255);
		return ;
	}
	if (ft_strslen(args) == 2 && args[1])
	{
		if (!check_exit_value(args[1]))
			print_error_and_free(data, args);
	}
	if (args[1])
	{
		exit_value = ft_atoi(args[1]);
		close_limiters(data->tokens);
		free_memory(data, args);
		exit(exit_value);
	}
	close_limiters(data->tokens);
	free_memory(data, args);
	exit(g_status);
}

static void	print_error_and_free(t_data *data, char **args)
{
	print_error3("bashbros: ", "exit: ", args[1], " numeric argument required");
	close_limiters(data->tokens);
	free_memory(data, args);
	exit(2);
}
