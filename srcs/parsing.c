#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

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
	if (type == NAME)
		return ("NAME");
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
		return (create_token(str, NAME));
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
