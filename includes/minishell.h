#ifndef MINISHELL_H
# define MINISHELL_H

# define NONEWLINE 'N'
# define NEWLINE 'n'

typedef struct s_data		t_data;
typedef struct s_token		t_token;
typedef struct s_operators	t_operators;

typedef enum e_type
{
	NAME,
	CMD,
	FLAG,
	OPERATOR,
	WILDCARD,
	VARIABLE,
}							t_type;

// General struct
typedef struct s_data
{
	char					**env;
	t_token					**tokens;
	t_operators				*operators;

}							t_data;

// Token struct
typedef struct s_token
{
	void					*content;
	t_type					type;

}							t_token;

typedef struct s_operators
{
	char					pipe;
	char					space;
	char					redirection_t;
	char					redirection_f;
	char					*double_pipe;
	char					*op_and;
	char					*append;
	char					*here_doc;
}							t_operators;

t_token						**parse_cmd(t_data *data, char *cmd);
char						*pathfinder(const char *cmd, char **env);
void						print_tokens(t_token **tokens);

// Built ins

void						custom_echo(char *buf, void *content);
void						clean_exit(char *buf);
void						custom_pwd(char *buf);
void						custom_chdir(char *buf, char *path);

t_token						*create_token(void *content, t_type type);
t_token						*assign_token(t_token **tokens, char *str,
								int index);
void						print_tokens(t_token **tokens);
char						*get_enum(t_type type);
void						custom_env(char *buf, char **env);
char						**ft_split_v2(t_data *data, char *str);

#endif // !
