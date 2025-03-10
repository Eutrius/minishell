/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:33:57 by lonulli           #+#    #+#             */
/*   Updated: 2025/03/07 22:33:57 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
// clang-format off
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
// clang-format on
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

void	handle_redirect_input(t_data *data, t_token *root, int *fd)
{
	char	*file;

	file = expand_files((char *)root->left->content);
	if (!file)
	{
		g_status = 1;
		return ;
	}
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
	{
		print_error2("Failed to redirect input: ", (char *)root->left->content,
			"file not found", 1);
		free_memory(data, NULL);
		g_status = 1;
		return ;
	}
	custom_dup2(*fd, "STDIN");
	if (close(*fd) == -1)
		print_error(ERR_CLOSEFD, 1);
}

void	handle_redirect_output(t_data *data, t_token *root, int *fd)
{
	char	*file;

	file = expand_files((char *)root->left->content);
	if (!file)
	{
		g_status = 1;
		return ;
	}
	*fd = open((char *)root->left->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
	{
		print_error2("Failed to redirect output: ", (char *)root->left->content,
			"\n", 1);
		free_memory(data, NULL);
		g_status = 1;
		return ;
	}
	custom_dup2(*fd, "STDOUT");
	if (close(*fd) == -1)
		print_error(ERR_CLOSEFD, 1);
}

void	handle_redirect_append(t_data *data, t_token *root, int *fd)
{
	char	*file;

	file = expand_files((char *)root->left->content);
	if (!file)
	{
		g_status = 1;
		return ;
	}
	*fd = open((char *)root->left->content, O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (*fd == -1)
	{
		print_error1("Failed to redirect output: ", (char *)root->left->content,
			1);
		free_memory(data, NULL);
		return ;
	}
	custom_dup2(*fd, "STDOUT");
	if (close(*fd) == -1)
		print_error(ERR_CLOSEFD, 1);
}

void	handle_redirect_heredoc(t_token *root, int *fd)
{
	fd = (int *)root->left->content;
	custom_dup2(*fd, "STDIN");
}
