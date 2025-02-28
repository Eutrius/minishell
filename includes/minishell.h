#ifndef MINISHELL_H
# define MINISHELL_H

# define NONEWLINE 'N'
# define NEWLINE 'n'
# define ERR_MALLOC "minishell: memory allocation failed"
# define ERR_SYNTAX "minishell: syntax error"

typedef struct s_data		t_data;
typedef struct s_token		t_token;
typedef struct s_operators	t_operators;
typedef struct s_parser		t_parser;

extern int					g_status;

typedef enum e_type
{
	NONE = 1 << 0,
	PIPE = 1 << 1,
	OR = 1 << 2,
	AND = 1 << 3,
	OPEN = 1 << 4,
	CLOSE = 1 << 5,
	HERE_DOC = 1 << 6,
	R_IN = 1 << 7,
	APPEND = 1 << 8,
	R_OUT = 1 << 9,
	END = 1 << 10,
	START = 1 << 11,
	NAME = 1 << 13,
	CMD = 1 << 14,
	DELIMITER = 1 << 15,
	REDIRECT = 1 << 16,
	FILENAME = 1 << 17,
	LIMITER = 1 << 18,

}							t_type;

typedef enum e_mode
{
	NORMAL,
	QUOTE,
	OPERATOR,

}							t_mode;

// General struct

typedef struct s_data
{
	char					**env;
	t_token					*root;
	t_token					**cmd_line;
	t_parser				*parser;

}							t_data;

typedef struct s_parser
{
	t_data					*data;

	// split
	char					*buffer;
	t_token					**tokens;
	t_token					*token;
	char					*str;
	t_type					last_token;

	// check
	int						parentesis;

}							t_parser;

// Token struct

typedef struct s_token
{
	void					*content;
	t_type					sub_type;
	int						index;
	t_type					type;
	t_token					*left;
	t_token					*right;

}							t_token;

// Init

void						init(t_data *data, t_parser *parser);
void						init_operators(t_operators *operators);

// Parse

int							parse(t_data *data);
int							split_line(t_parser *parser);
int							check_line(t_parser *parser);
void						prepare_line(t_parser *parser);
t_token						*parse_line(t_token **tokens);
void						parse_error(t_parser *parser);
int							gen_token(t_parser *parser, t_mode mode);
int							is_special(int c);
int							is_dquote(int c);
int							is_quote(int c);
void						extract(t_parser *parser, int *index,
								int (*ctrl)(int), t_mode mode);
void						expand_variable(t_parser *parser);
void						join_last(t_parser *parser);
char						*if_double(char *str, int *index, char *twice,
								char *once);
void						count_parentesis(int *parentesis, t_token *token);

void						print_tokens(t_token **tokens);
void						print_tree(t_token *root, int level);

// Token

void						free_token(t_token *token);
void						free_tokens(t_token **tokens);
t_token						*create_token(void *content, t_type type);
t_token						**add_token(t_token **tokens, t_token *token);

// Expand

void						check_value(t_data *data);
int							calculate_var_len(char *str);
int							is_valid(char c);

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
int							var_exists(char **env, char *to_check);
void						free_previous_sorted_exp(char **exported_dup,
								int i);
void						value_checker(char **sorted_exp, int i);

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

char						*get_enum(t_type type);

// Utils

int							print_error(char *msg);
int							print_error1(char *msg, char *msg1);
int							print_error2(char *msg, char *msg1, char *msg2);
int							print_error3(char *msg, char *msg1, char *msg2,
								char *msg3);

#endif // !
