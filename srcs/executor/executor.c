#include "libft.h"
#include "minishell.h"
// clang-format off
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
// clang-format on
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

int			execute_cmd(char **args, t_data *data);
static void	handle_redirects(t_data *data, t_token *root);
// static void handle_pipe(t_token *root,t_data *data, char **args);
void		check_fork(pid_t pid, int wefd, int refd);

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
	char	**args;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	// pid_t	pid3;
	if (root == NULL)
		return ;
	if (root->sub_type & CMD)
	{
		args = fill_args_array(root, data);
		if (args)
		{
			execute_cmd(args, data);
			free(args);
		}
	}
	else if (root->sub_type & PIPE)
	{
		pipe(pipefd);
		pid1 = fork();
		if (pid1 == 0)
		{
			close(pipefd[0]);
			custom_dup2(pipefd[1], "STDOUT");
			close(pipefd[1]);
			executor(data, root->left);
			exit(g_status);
		}
		waitpid(pid1, &g_status, 0);
		pid2 = fork();
		if (pid2 == 0)
		{
			close(pipefd[1]);
			custom_dup2(pipefd[0], "STDIN");
			close(pipefd[0]);
			executor(data, root->right);
			exit(g_status);
		}
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(pid2, &g_status, 0);
	}
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
	{
		handle_redirects(data, root);
		executor(data, root->right);
	}
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
	int		idx;
	t_token	**cmd_array;
	char	**args;

	i = 0;
	idx = cmd->index;
	cmd_array = data->cmd_line;
	i = idx;
	while (cmd_array[i] && (cmd_array[i]->type & CMD))
		i++;
	args = ft_calloc(i - idx + 1, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (cmd_array[idx] && (cmd_array[idx]->type & CMD))
	{
		args[i] = cmd_array[idx]->content;
		idx++;
		i++;
	}
	return (args);
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

int	execute_cmd(char **args, t_data *data)
{
	pid_t	pid;
	char	*cmd_path;

	if (is_builtin(args, data))
	{
		g_status = 0;
		return (0);
	}
	cmd_path = pathfinder(args[0], data->env);
	if (!cmd_path)
	{
		print_error2("B_bros ", args[0], " command not found");
		g_status = 127;
		return (1);
	}
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
		return (g_status);
	}
	return (0);
}

static void	handle_redirects(t_data *data, t_token *root)
{
	int	fd;

	if (root == NULL)
		return ;
	if (root->sub_type & (R_IN | R_OUT | APPEND))
	{
		if (root->sub_type & R_IN)
			handle_redirect_input(data, root, &fd);
		else if (root->sub_type & R_OUT)
			handle_redirect_output(data, root, &fd);
		else
			handle_redirect_append(data, root, &fd);
	}
}

void	check_fork(pid_t pid, int wefd, int refd)
{
	if (pid < 0)
	{
		close(wefd);
		close(refd);
		ft_putstr_fd(strerror(errno), 2);
		exit(EXIT_FAILURE);
	}
}
