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


static char **ft_strsjoin(char **strs_dest, char **strs_join);

char **expand_cmd(char **args)
{
	int i;
	i = 0;
	char **new_args = ft_calloc(1,sizeof(char *));
	while(args[i])
	{

		char **expanded_arg = expand_wildcard(args[i]);
		if (expanded_arg == NULL)
		{
			remove_quotes(args[i]);
			char *tmp = ft_strdup(args[i]);
			if (!tmp)
			{
				ft_free_strs(args);
				ft_free_strs(new_args);
				return NULL;
			}
			new_args =ft_strscat(new_args,tmp);
		}
		else
			new_args = ft_strsjoin(new_args,expanded_arg);
		if (!new_args)
		{
			free(new_args);
			return NULL;
		}
		i++;
	}
	ft_free_strs(args);
	return new_args;
}

char *expand_files(char *file)
{
	char **new_files = expand_wildcard(file);
	int num_strings  = ft_strslen(new_files);
	if (num_strings > 1)
	{
		print_error2("bashbros: ",file," Ambigous redirect");
		return NULL;
	}
	else if (num_strings == 1)
		return new_files[0];
	else
	{
		remove_quotes(file);
		return file;
	}
	return NULL;
}

static char **ft_strsjoin(char **strs_dest, char **strs_join)
{
	int strs_dest_len = ft_strslen(strs_dest);
	int strs_join_len = ft_strslen(strs_join);
	char **res = ft_calloc((strs_dest_len + strs_join_len + 1),sizeof(char *));
	if (!res)
		return NULL;
	int i = 0;
	int j = 0;
	while(strs_dest && strs_dest[i])
	{
		res[i] = strs_dest[i];
		i++;
	}
	while(strs_join && strs_join[j])
	{
		res[i] = strs_join[j];
		j++;
		i++;
	}
	free(strs_dest);
	free(strs_join);
	return res;
}


// int			execute_cmd(char **args, t_data *data);
// // static void	handle_redirects(t_token *root);
// // static void handle_pipe(t_token *root,t_data *data, char **args);
// void		check_fork(pid_t pid, int wefd, int refd);

// void handle_basic_cmd(t_data *data, t_token *root)
// {
// 	char **args = fill_args_array(root, data);
// 	if (args)
// 	{
// 		execute_cmd(args, data);
// 		free(args);
// 	}
// }

// void handle_pipe(t_data *data, t_token *root)
// {
// 	int pipefd[2];
// 	pid_t pid1;
// 	pid_t pid2;

// 	pipe(pipefd);
// 	pid1 = fork();
// 	if (pid1 == 0)
// 	{
// 		close(pipefd[0]);
// 		custom_dup2(pipefd[1], "STDOUT");
// 		close(pipefd[1]);
// 		executor(data, root->left);
// 		exit(g_status);
// 	}
// 	pid2 = fork();
// 	if (pid2 == 0)
// 	{
// 		close(pipefd[1]);
// 		custom_dup2(pipefd[0], "STDIN");
// 		close(pipefd[0]);
// 		executor(data, root->right);
// 		exit(g_status);
// 	}
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	waitpid(pid1, &g_status, 0);
// 	waitpid(pid2, &g_status, 0);
// }

// void handle_and_operator(t_data *data, t_token *root)
// {
// 	executor(data, root->left);
// 		if (g_status == 0)
// 			executor(data, root->right);
// }

// void handle_or_operator(t_data *data, t_token *root)
// {
// 	executor(data, root->left);
// 		if (g_status != 0)
// 			executor(data, root->right);
// }

// void redirects(t_data *data, t_token *root)
// {
// 	pid_t pid3;

// 	pid3 = fork();
// 		if (pid3 == 0)
// 		{
// 			handle_redirects(root);
// 			if (g_status != 0)
// 				exit(g_status);
// 			if (root->left && root->left->sub_type & CMD)
// 				executor(data, root->left);
// 			else if (root->right && !(root->right->sub_type & (PIPE)))
// 				executor(data, root->right);
// 			exit(g_status);
// 		}
// 		else if (pid3 > 0)
// 		{
// 			waitpid(pid3, &g_status, 0);
// 			if (WIFEXITED(g_status))
// 				g_status = WEXITSTATUS(g_status);
// 		}
// 		else
// 		{
// 			print_error1("Failed to create process for redirection", "");
// 			g_status = 1;
// 		}
// }
