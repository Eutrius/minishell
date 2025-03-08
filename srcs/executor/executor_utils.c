/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:33:42 by lonulli           #+#    #+#             */
/*   Updated: 2025/03/07 22:33:43 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
// clang-format off
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
// clang-format on
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

static int	first_command(t_data *data, t_token *root, int *pipefd);
static int	second_command(t_data *data, t_token *root, int *pipefd);

void	handle_redirect(t_data *data, t_token *root)
{
	pid_t	pid3;

	pid3 = fork();
	if (pid3 == 0)
	{
		filter_redirects(data, root);
		if (g_status != 0)
			exit(g_status);
		executor(data, root->right);
		free_memory(data, NULL);
		exit(g_status);
	}
	else if (pid3 > 0)
	{
		waitpid(pid3, &g_status, 0);
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
	}
	else
		print_error("Failed to create process for redirection", 1);
}

void	handle_pipe(t_data *data, t_token *root)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (custom_pipe(pipefd) == 0)
		return ;
	if (custom_fork(&pid1) == -1)
		return ;
	if (pid1 == 0)
	{
		if (first_command(data, root, pipefd) == 0)
			return ;
	}
	if (custom_fork(&pid2) == -1)
		return ;
	if (pid2 == 0)
	{
		if (second_command(data, root, pipefd) == 0)
			return ;
	}
	close_fds(pipefd[1], pipefd[0]);
	waitpid(pid1, &g_status, 0);
	waitpid(pid2, &g_status, 0);
}

static int	first_command(t_data *data, t_token *root, int *pipefd)
{
	if (custom_dup2(pipefd[1], "STDOUT") == 0)
		return (0);
	close_fds(pipefd[1], pipefd[0]);
	executor(data, root->left);
	free_memory(data, NULL);
	exit(g_status);
}

static int	second_command(t_data *data, t_token *root, int *pipefd)
{
	if (custom_dup2(pipefd[0], "STDIN") == 0)
		return (0);
	close_fds(pipefd[1], pipefd[0]);
	executor(data, root->right);
	free_memory(data, NULL);
	exit(g_status);
}

void	signal_setup(t_data *data, char **args, char *flag)
{
	if (ft_strcmp(flag, "CHILD") == 0 && set_signal(SIGQUIT, handle_quit))
	{
		free_memory(data, NULL);
		exit(print_error(ERR_SIGACTION, 1));
	}
	if (ft_strcmp(flag, "PARENT") == 0 && (set_signal(SIGQUIT, SIG_IGN)
			|| set_signal(SIGINT, SIG_IGN)))
	{
		free_memory(data, args);
		exit(print_error(ERR_SIGACTION, 1));
	}
}
