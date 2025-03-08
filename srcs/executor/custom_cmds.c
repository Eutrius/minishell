/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:33:30 by lonulli           #+#    #+#             */
/*   Updated: 2025/03/07 22:33:38 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
// clang-format off
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
// clang-format on
#include <string.h>
#include <unistd.h>

int	custom_dup2(int fd, char *flag)
{
	if (!ft_strcmp(flag, "STDIN"))
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			g_status = errno;
			return (1);
		}
	}
	else if (!ft_strcmp(flag, "STDOUT"))
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			g_status = errno;
			return (0);
		}
	}
	return (1);
}

int	custom_pipe(int fds[2])
{
	if (pipe(fds) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		g_status = errno;
		return (0);
	}
	return (1);
}

int	close_fds(int wefd, int refd)
{
	if (close(wefd) == -1 || close(refd) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		g_status = errno;
		return (0);
	}
	return (1);
}

int	custom_fork(int *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork failed");
		g_status = errno;
		return (-1);
	}
	return (1);
}

int	custom_unlink(char *filepath)
{
	if (unlink(filepath) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (0);
	}
	return (1);
}
