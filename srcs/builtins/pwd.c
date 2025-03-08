/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:34:26 by lonulli           #+#    #+#             */
/*   Updated: 2025/03/07 22:34:27 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	custom_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
	{
		perror("Error");
		g_status = 1;
		return ;
	}
  g_status = 0;
	printf("%s\n", buf);
	free(buf);
}
