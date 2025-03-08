/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:41:47 by jyriarte          #+#    #+#             */
/*   Updated: 2025/03/06 16:00:30 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void	init(t_data *data, t_parser *parser)
{
	extern char	**environ;

	data->parser = parser;
	parser->data = data;
	data->env = ft_strsdup(environ);
	if (!data->env)
	{
		print_error(ERR_MALLOC, 1);
		exit(1);
	}
	data->stdin_orig = dup(STDIN_FILENO);
	data->stdout_orig = dup(STDOUT_FILENO);
}
