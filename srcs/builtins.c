/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:08:15 by lonulli           #+#    #+#             */
/*   Updated: 2025/02/18 14:08:16 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void	custom_echo(char *buf, void *content)
{
	if (!ft_strcmp(buf, "echo"))
		printf("%s\n", (char *)content);
}

void	clean_exit(char *buf)
{
	if (!ft_strcmp(buf, "exit"))
		exit(0);
}

void	custom_pwd(char *buf)
{
	if (!ft_strcmp(buf, "pwd"))
	{
		buf = getcwd(NULL, 0);
		if (buf == NULL)
		{
			perror("Error");
			return ;
		}
		printf("%s\n", buf);
		free(buf);
	}
}

void	custom_chdir(char *buf, char *path)
{
	if (!ft_strcmp(buf, "cd"))
	{
		if (chdir(path) == -1)
			perror("Error");
	}
}
