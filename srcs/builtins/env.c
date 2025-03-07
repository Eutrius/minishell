/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:34:10 by lonulli           #+#    #+#             */
/*   Updated: 2025/03/07 22:34:11 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	find_equal_index(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	custom_env(t_data *data)
{
	int	i;
	int	eq_i;

	i = 0;
	while (data->env && data->env[i] != NULL)
	{
		eq_i = find_equal_index(data->env[i]);
		if (ft_strchr(data->env[i], '=') && (data->env[i][eq_i + 1]))
			printf("%s\n", data->env[i]);
		i++;
	}
}
