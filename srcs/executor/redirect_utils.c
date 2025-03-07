#include "libft.h"
#include "minishell.h"
// clang-format off
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
// clang-format on
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
void	handle_redirect_input(t_token *root, int *fd)
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
			"file not found");
		g_status = 1;
		return ;
	}
	dup2(*fd, STDIN_FILENO);
	close(*fd);
}

void	handle_redirect_output(t_token *root, int *fd)
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
			"\n");
		g_status = 1;
		return ;
	}
	dup2(*fd, STDOUT_FILENO);
	close(*fd);
}

void	handle_redirect_append(t_token *root, int *fd)
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
		print_error1("Failed to redirect output: ",
			(char *)root->left->content);
		g_status = 1;
		return ;
	}
	dup2(*fd, STDOUT_FILENO);
	close(*fd);
}

void	handle_redirect_heredoc(t_token *root, int *fd)
{
	fd = (int *)root->left->content;
	dup2(*fd, STDIN_FILENO);
}
