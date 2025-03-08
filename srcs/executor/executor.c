/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <lonulli@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:33:47 by lonulli           #+#    #+#             */
/*   Updated: 2025/03/07 22:33:48 by lonulli          ###   ########.fr       */
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
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>

static int	fork_command(t_data *data, char *cmd_path, char **args);

void	executor(t_data *data, t_token *root)
{
	if (root == NULL)
		return ;
	if (root->sub_type & CMD)
		execute_cmd(root, data);
	else if (root->sub_type & PIPE)
		handle_pipe(data, root);
	else if (root->sub_type & AND)
	{
		executor(data, root->left);
		if (g_status == 0)
			executor(data, root->right);
	}
	else if (root->sub_type & OR)
	{
		executor(data, root->left);
		if (g_status != 0)
			executor(data, root->right);
	}
	else if (root->sub_type & (R_IN | R_OUT | APPEND | HERE_DOC))
		handle_redirect(data, root);
}

int	execute_cmd(t_token *root, t_data *data)
{
	char	*cmd_path;
	char	**args;

	args = fill_args_array(root, data);
	args = expand_cmd(args);
	if (args == NULL)
	{
		print_error(ERR_MALLOC, 1);
		return (0);
	}
	if (is_builtin(args, data))
	{
		ft_free_strs(args);
		return (0);
	}
	cmd_path = pathfinder(args[0], data->env);
	if (!cmd_path)
	{
		print_error2("B_bros ", args[0], " command not found", 127);
		ft_free_strs(args);
		return (1);
	}
	return (fork_command(data, cmd_path, args));
}

void	filter_redirects(t_data *data, t_token *root)
{
	int	fd;

	if (root == NULL)
		return ;
	if (root->sub_type & (R_IN | R_OUT | APPEND | HERE_DOC))
	{
		if (root->sub_type & R_IN)
			handle_redirect_input(data, root, &fd);
		else if (root->sub_type & R_OUT)
			handle_redirect_output(data, root, &fd);
		else if (root->sub_type & APPEND)
			handle_redirect_append(data, root, &fd);
		else
			handle_redirect_heredoc(root, &fd);
	}
}

static int	fork_command(t_data *data, char *cmd_path, char **args)
{
	pid_t	pid;

	if (custom_fork(&pid) == -1)
		return (0);
	if (pid == 0)
	{
		signal_setup(data, args, "CHILD");
		if (execve(cmd_path, args, data->env) == -1)
		{
			free(cmd_path);
			g_status = 1;
			exit(126);
		}
	}
	else
	{
		signal_setup(data, args, "PARENT");
		waitpid(pid, &g_status, 0);
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
		free(cmd_path);
		ft_free_strs(args);
		return (g_status);
	}
	return (0);
}

char	**fill_args_array(t_token *cmd, t_data *data)
{
	int		i;
	t_token	**cmds;
	char	**args;

	cmds = data->tokens;
	i = cmd->index;
	while (cmds[i] && (cmds[i]->type & CMD))
		i++;
	args = ft_calloc(i - cmd->index + 2, sizeof(char *));
	i = 0;
	while (args && cmds[cmd->index + i] && (cmds[cmd->index + i]->type & CMD))
	{
		args[i] = ft_strdup(cmds[cmd->index + i]->content);
		if (!args[i])
		{
			print_error(ERR_MALLOC, 1);
			ft_free_strs(args);
			return (NULL);
		}
		i++;
	}
	return (args);
}
