/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:34:08 by lonulli           #+#    #+#             */
/*   Updated: 2025/03/07 22:34:08 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

// static void	print_without_flag(char **args);
// static void	print_with_flag(char **args);
static int	is_flag(char *args);

void	custom_echo(char **args)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = 0;
	if (!args || !args[0])
		return ;
	while (args[i] && is_flag(args[i]))
	{
		no_newline = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
	g_status = 0;
}

static int	is_flag(char *args)
{
	int	i;

	i = 2;
	if (args[0] != '-' || args[1] != 'n')
		return (0);
	while (args[i])
	{
		if (args[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
