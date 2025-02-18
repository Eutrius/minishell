#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_token	*create_token(void *content, t_type type);
t_token	**parse_cmd(char *cmd);
t_token	*assign_token(t_token **tokens, char *str, int index);
void	print_tokens(t_token **tokens);
char	*get_enum(t_type type);

int	main(void)
{
	char	*buf;
	t_data	data;

	while (1)
	{
		buf = readline("B_bros > ");
		if (!buf || !ft_strcmp(buf, "exit"))
			exit(0);
		add_history(buf);
		data.cmd = parse_cmd(buf);
		print_tokens(data.cmd);
		free(buf);
	}
	return (0);
}

void	print_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		printf("content: %s, %s\n", (char *)tokens[i]->content,
			get_enum(tokens[i]->type));
		i++;
	}
}

char	*get_enum(t_type type)
{
	if (type == FILENAME)
		return ("FILENAME");
	if (type == CMD)
		return ("CMD");
	if (type == FLAG)
		return ("FLAG");
	if (type == WILDCARD)
		return ("WILDCARD");
	return ("OTHERS");
}

t_token	**parse_cmd(char *cmd)
{
	char	**strs;
	t_token	**tokens;
	int		i;

	strs = ft_split(cmd, ' ');
	if (!strs)
		return (NULL);
	tokens = ft_calloc((ft_strslen(strs) + 1), sizeof(t_token *));
	if (!tokens)
	{
		ft_free_strs(strs);
		return (NULL);
	}
	i = 0;
	while (strs[i] != NULL)
	{
		tokens[i] = assign_token(tokens, strs[i], i);
		i++;
	}
	free(strs);
	return (tokens);
}

t_token	*assign_token(t_token **tokens, char *str, int index)
{
	if (str[0] == '-' && ft_strlen(str) != 0)
		return (create_token(str, FLAG));
	else if (str[0] == '*')
		return (create_token(str, WILDCARD));
	else if (str[0] == '$')
		return (create_token(str, VARIABLE));
	else if (!ft_strcmp(str, ";"))
		return (create_token(str, OPERATOR));
	else if (!ft_strcmp(str, "|"))
		return (create_token(str, OPERATOR));
	else if (!ft_strcmp(str, "&&"))
		return (create_token(str, OPERATOR));
	else if (!ft_strcmp(str, "||"))
		return (create_token(str, OPERATOR));
	else if (index == 0)
		return (create_token(str, CMD));
	else if (index != 0 && !ft_strcmp(tokens[index - 1]->content, ";"))
		return (create_token(str, CMD));
	else if (index != 0 && !ft_strcmp(tokens[index - 1]->content, "|"))
		return (create_token(str, CMD));
	else if (index != 0 && !ft_strcmp(tokens[index - 1]->content, "&&"))
		return (create_token(str, CMD));
	else
		return (create_token(str, FILENAME));
}

t_token	*create_token(void *content, t_type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = content;
	token->type = type;
	return (token);
}
