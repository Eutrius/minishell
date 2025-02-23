#ifndef MINISHELL_H
# define MINISHELL_H

# define NONEWLINE 'N'
# define NEWLINE 'n'
# define ERR_MALLOC "minishell: memory allocation failed\n"
# define ERR_SYNTAX "minishell: syntax error\n"

typedef struct s_data		t_data;
typedef struct s_token		t_token;
typedef struct s_operators	t_operators;
typedef struct s_parser		t_parser;

extern int					g_status;

typedef enum e_type
{
	NAME,
	CMD,
	FLAG,
	OPERATOR,
	WILDCARD,
	VARIABLE,
}							t_type;

typedef enum e_mode
{
	NORMAL,
	QUOTE,
	DQUOTE,
}							t_mode;

// General struct

typedef struct s_data
{
	char					**env;
	t_token					***cmd_lines;
	t_token					**cmd_line;
	t_parser				*parser;

}							t_data;

typedef struct s_parser
{
	t_data					*data;
	char					*buffer;
	char					**strs;
	int						skipped;
}							t_parser;

// Token struct

typedef struct s_token
{
	void					*content;
	t_type					type;

}							t_token;

// Init

void						init(t_data *data, t_parser *parser);
void						init_operators(t_operators *operators);

// Parse

void						split_cmd(t_parser *parser);
void						parse_cmd(t_data *data);
int							is_special(int c);
int							is_dquote(int c);
int							is_quote(int c);
void						extract_str(t_parser *parser, int *index,
								int (*f)(int), t_mode mode);
void						extract_op(t_parser *parser, int *index);
void						parse_strs_error(char ***strs, char *msg);
void						print_error(char *msg);

// Execute

char						*pathfinder(const char *cmd, char **env);

// Built in Utils

int							check_exit_value(char *str);
int							count_tokens(t_token **token);
int							is_builtin(char *buf, t_data *data);
int							strs_count(char **strs);
void						print_string_array(char **strs);
int							is_valid_identifier(char *str);
int							find_eq_i(char *str);

// Pathfinder
char						*pathfinder(const char *cmd, char **env);

// Built in

void						custom_echo(t_data *data);
void						clean_exit(t_data *data);
void						custom_pwd(void);
void						custom_chdir(t_data *data);
void						custom_env(t_data *data);
void						custom_export(t_data *data);
void						custom_unset(t_data *data);

t_token						*create_token(void *content, t_type type);
t_token						*assign_token(t_token **tokens, char *str,
								int index);
void						print_tokens(t_token **tokens);
char						*get_enum(t_type type);

#endif // !
