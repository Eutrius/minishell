#include "minishell.h"
// clang-format off
#include <readline/history.h>
#include <readline/readline.h>
// clang-format on
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

void	handle_redirect(t_data *data, t_token *root)
{
	pid_t	pid3;

	pid3 = fork();
	if (pid3 == 0)
	{
		filter_redirects(root);
		if (g_status != 0)
			exit(g_status);
		executor(data, root->right);
		exit(g_status);
	}
	else if (pid3 > 0)
	{
		waitpid(pid3, &g_status, 0);
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
	}
	else
	{
		print_error1("Failed to create process for redirection", "");
		g_status = 1;
	}
}

void	handle_pipe(t_data *data, t_token *root)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	// pipe(pipefd);
	custom_pipe(pipefd);
	pid1 = fork();
	// check_fork(pid1,pipefd[1],pipefd[0]);
	if (pid1 == 0)
	{
		custom_dup2(pipefd[1], "STDOUT");
		close_fds(pipefd[1], pipefd[0]);
		executor(data, root->left);
		exit(g_status);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		custom_dup2(pipefd[0], "STDIN");
		close_fds(pipefd[1], pipefd[0]);
		executor(data, root->right);
		exit(g_status);
	}
	close_fds(pipefd[1], pipefd[0]);
	waitpid(pid1, &g_status, 0);
	waitpid(pid2, &g_status, 0);
}
