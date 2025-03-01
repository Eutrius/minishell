#include "libft.h"
#include "minishell.h"
// clang-format off
#include <readline/history.h>
#include <readline/readline.h>
// clang-format on
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

void	execute_cmd(char **args, t_data *data);
static void handle_redirects(t_token *root);

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

void execute_cmd(char **args, t_data *data)
{
	pid_t pid;
	char *cmd_path;
  int status;
	t_token **token_array = data->cmd_line;
	t_token *token = token_array[0];

  handle_redirects(data->root);
	cmd_path = pathfinder(token->content,data->env);
  if (!cmd_path)
  {
    print_error2("minishell ",args[0],"command not found");
    g_status = 127;
    return ;
  }
  pid = fork();
  if (pid == 0)
  {
    if (execve(cmd_path,args,data->env) == -1)
    {
      free(cmd_path);
      g_status = 1;
      exit(126);
    }
  }
  else
  {
    waitpid(pid,&status,0);
    free(cmd_path);
  }
}

// static void handle_pipe(t_token *root)
// {
//   int pipe_fd[2];

//   if (root->sub_type & PIPE)
//   {

//   }
//   handle_pipe(root->left);
//   handle_pipe(root->right);

// }

static void handle_redirects(t_token *root)
{
  if (root == NULL)
        return;
  if (root->sub_type & (R_IN | R_OUT | APPEND | PIPE))
  {
    int fd = -1;
    int pipe_fds[2];

    if (root->sub_type & R_IN)
    {
      fd = open((char *)root->left->content, O_RDONLY);
      if (fd == -1)
      {
        print_error2("Failed to redirect input: ", (char *)root->left->content, "file not found");
        g_status = 1;
        return ;
      }
      custom_dup2(fd,"STDIN");
    }
    else if (root->sub_type & R_OUT)
    {
      fd = open((char *)root->left->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
      if (fd == -1)
      {
        print_error2("Failed to redirect output: ", (char *)root->left->content, "\n");
        g_status = 1;
        return ;
      }
      custom_dup2(fd,"STDOUT");
    }
    else if (root->sub_type & APPEND)
    {
      fd = open((char *)root->left->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
      if (fd == -1)
      {
        print_error1("Failed to redirect output: ", (char *)root->left->content);
        g_status = 1;
        return ;
      }
      custom_dup2(fd,"STDOUT");
    }
    else if (root->sub_type & PIPE)
    {
      custom_pipe(pipe_fds);
    }
    close(fd);
  }
  handle_redirects(root->left);
  handle_redirects(root->right);
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
