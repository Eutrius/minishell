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

void	execute_cmd(t_token *cur_root, char **args, t_data *data);
static void handle_redirects(t_token *root);
static void handle_pipe(t_token *root,t_data *data, char **args);

void executor(char **args,t_data *data)
{
  args = fill_args_array(data->root,data);
  handle_redirects(data->root);
  handle_pipe(data->root,data,args);
}

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

void execute_cmd(t_token *cur_root, char **args, t_data *data)
{
	pid_t pid;
	char *cmd_path;
  int status;
  printf("Executing command: %s\n",args[0]);

  handle_redirects(cur_root);
  if (is_builtin(args,data))
    return;
  cmd_path = pathfinder(args[0],data->env);
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

static void handle_pipe(t_token *root,t_data *data, char **args)
{
  int pipe_fd[2];
  pid_t pid1;
  pid_t pid2;
  char **left_args;
  char **right_args;

  if (!root)
    return;
    
  if (root->sub_type & PIPE)
  {
    if (pipe(pipe_fd) == -1)
    {
      perror("pipe");
      exit(EXIT_FAILURE);
    }
    pid1 = fork();
    if (pid1 < 0)
    {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    if (pid1 == 0)
    {
      custom_dup2(pipe_fd[1],"STDOUT");
      close_fds(pipe_fd[1],pipe_fd[0]);
      if (root->left->sub_type & PIPE)
        handle_pipe(root->left,data,args);
      else
      {
        left_args = fill_args_array(root->left,data);
        execute_cmd(root->left,left_args,data);
        free(left_args);
      }
      exit(EXIT_SUCCESS);
    }


    pid2 = fork();
    if (pid2 < 0)
    {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    if (pid2 == 0) 
    {
      dup2(pipe_fd[0], STDIN_FILENO);
      close_fds(pipe_fd[1],pipe_fd[0]);
      if (root->right->sub_type & REDIRECT)
        handle_redirects(root->right);
      else
      {
        right_args = fill_args_array(root->right,data);
        execute_cmd(root->right,right_args,data);
        free(right_args);
      }
      exit(EXIT_SUCCESS);
    }
    close_fds(pipe_fd[1],pipe_fd[0]);
    waitpid(pid1,&g_status, 0);
    waitpid(pid2,&g_status, 0);
    return;
  }
  handle_pipe(root->left,data,args);
  handle_pipe(root->right,data,args);
}

static void handle_redirects(t_token *root)
{
  if (root == NULL)
        return;
  if (root->sub_type & (R_IN | R_OUT | APPEND | PIPE))
  {
    int fd;
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
      close(fd);
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
      close(fd);
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
      close(fd);
    }
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
