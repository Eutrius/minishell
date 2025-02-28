#include "libft.h"
#include "minishell.h"
// clang-format off
#include <readline/history.h>
#include <readline/readline.h>
// clang-format on
#include <unistd.h>

void execute_cmd(char **args, t_token *cmd, t_data *data);
// static int redirect_in(t_token *redirect);
// static int redirect_out(t_token *redirect);

char **fill_args_array(t_token *cmd, t_data *data)
{
	int i = 0;
	int idx =  cmd->index;
	t_token **cmd_array = data->cmd_line;
	i = idx;
	while (cmd_array[i] && (cmd_array[i]->type & CMD))
		i++;
	char **args = ft_calloc(i - idx + 1, sizeof(char *));
	if (!args)
		return NULL;
	i = 0;
	while(cmd_array[idx] && (cmd_array[idx]->type & CMD))
	{
		args[i] = cmd_array[idx]->content;
		idx++;
		i++;
	}
	return args;
}

// void execute_cmd(char **args,t_token *cmd, t_data *data)
// {
// 	pid_t pid;
// 	char *cmd_path;
// 	t_token **token_array = data->cmd_line;
// 	t_token *token = token_array[0];
// 	cmd_path = pathfinder(token->content,data->env);


// }
