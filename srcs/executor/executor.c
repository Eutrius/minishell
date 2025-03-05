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
#include <errno.h>
#include <fcntl.h>

static int	fork_command(t_data *data, char *cmd_path, char **args);
/* T_data *data : General data struct
 * t_token *root: Token at the top of the Binary tree.
 * Core of the execution.
 * Recursive function that call itselfs recursively.
 * The tree structure at this pointe is already well defined
 * so we can safely navigate it.
 * Once it found a certain token type, it handles it GRACEFULLY.
 */

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
	else if (root->sub_type & (R_IN | R_OUT | APPEND))
		handle_redirect(data, root);
}

/* Args: Array of strings that contains cmd name, flags etc.
 * Data: Pointer to a t_data struct (general struct)
 * Execute cmd will first check if a function is a built in or not.
 * If it's a builtin it will execute it. If its not a builtin
 * it will use Pathfinder on args[0] (cmd name).
 * Then it will just create sub process that will execute the cmd.
 * If process is not a child, we'll just wait for child process to end
 * and update g_status to its exit status.
 * */

int	execute_cmd(t_token *root, t_data *data)
{
	char	*cmd_path;
	char	**args;

	args = fill_args_array(root, data);
	if (!args)
		return (0);
	args = expand_cmd(args);
	if (is_builtin(args, data))
		return (0);
	cmd_path = pathfinder(args[0], data->env);
	if (!cmd_path)
	{
		print_error2("B_bros ", args[0], " command not found");
		g_status = 127;
		return (1);
	}
	return (fork_command(data, cmd_path, args));
}

/* T_TOKEN *CMD: Pointer to Structure T_token. (Current Token)
 * T_data *data: Pointer to a general Data struct.
 * Function to fill a string array with the various cmd_name flags and options.
 * It will search inside the cmd_line (Array of tokens) thanks to index
 * found inside given cmd_token.
 * It will allocate enough spaces for all the args that we will then use
 * inside execve.*/

char	**fill_args_array(t_token *cmd, t_data *data)
{
	int		i;
	t_token	**cmd_array;
	char	**args;

	cmd_array = data->cmd_line;
	i = cmd->index;
	while (cmd_array[i] && (cmd_array[i]->type & CMD))
		i++;
	args = ft_calloc(i - cmd->index + 1, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (cmd_array[cmd->index] && (cmd_array[cmd->index]->type & CMD))
	{
		args[i] = ft_strdup(cmd_array[cmd->index]->content);
		if (!args[i])
		{
			ft_free_strs(args);
			return (NULL);
		}
		cmd->index++;
		i++;
	}
	return (args);
}

static int	fork_command(t_data *data, char *cmd_path, char **args)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, args, data->env) == -1)
		{
			free(cmd_path);
			g_status = 1;
			exit(126);
		}
	}
	else
	{
		waitpid(pid, &g_status, 0);
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
		free(cmd_path);
		free(args);
		return (g_status);
	}
	return (0);
}

void	filter_redirects(t_token *root)
{
	int	fd;

	if (root == NULL)
		return ;
	if (root->sub_type & (R_IN | R_OUT | APPEND | HERE_DOC))
	{
		if (root->sub_type & R_IN)
			handle_redirect_input(root, &fd);
		else if (root->sub_type & R_OUT)
			handle_redirect_output(root, &fd);
		else if (root->sub_type & APPEND)
			handle_redirect_append(root, &fd);
		else
			handle_redirect_heredoc(root, &fd);
	}
}
