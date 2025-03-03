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

void handle_redirect_input(t_token *root, int *fd)
{
	if (root->sub_type & R_IN)
	{
		*fd = open((char *)root->left->content, O_RDONLY);
		if (*fd == -1)
		{
			print_error2("Failed to redirect input: ",
				(char *)root->left->content, "file not found");
			g_status = 1;
			return ;
		}
		dup2(*fd, STDIN_FILENO);
		close(*fd);
	}
}

void handle_redirect_output(t_token *root, int *fd)
{
	*fd = open((char *)root->left->content, O_WRONLY | O_CREAT | O_TRUNC,0644);
	if (*fd == -1)
	{
		print_error2("Failed to redirect output: ",
			(char *)root->left->content, "\n");
		g_status = 1;
		return ;
	}
	dup2(*fd, STDOUT_FILENO);
	close(*fd);
}

void handle_redirect_append(t_token *root, int *fd)
{
	*fd = open((char *)root->left->content,O_WRONLY | O_CREAT | O_APPEND, 0644);
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

void handle_redirect_heredoc(t_token *root)
{
	int tmp_file;
	char *line;
	char *limiter;

	tmp_file = open("tmp_file.txt", O_WRONLY | O_CREAT | O_APPEND,0644);
	if (root->left->sub_type & LIMITER)
		limiter = root->left->content;
	while(1)
	{
		line = readline(">");
		if (!line)
			break ;
		if (ft_strcmp(line,limiter) == 0)
			break ;
		ft_putstr_fd(line,tmp_file);
		ft_putchar_fd('\n',tmp_file);
		free(line);
		}
	close(tmp_file);
	tmp_file = open("tmp_file.txt", O_RDONLY);
	dup2(tmp_file,STDIN_FILENO);
	close (tmp_file);
	unlink("tmp_file.txt");
}
