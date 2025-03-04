#ifndef MINISHELL_H
# define MINISHELL_H

# define NONEWLINE 'N'
# define NEWLINE 'n'
# define ERR_MALLOC "b_bros: memory allocation failed"
# define ERR_SYNTAX "b_bros: syntax error"

typedef struct s_data		t_data;
typedef struct s_token		t_token;
typedef struct s_operators	t_operators;
typedef struct s_parser		t_parser;

extern int					g_status;

typedef enum e_type
{
	NONE = 0,
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
	CMD = 1 << 12,
	LIMITER = 1 << 13,
	DELIMITER = 1 << 14,
	REDIRECT = 1 << 15,
	FILENAME = 1 << 16,

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
	int						stdin_orig;
	int						stdout_orig;

	int						debug;

}							t_data;

typedef struct s_parser
{
	t_data					*data;
	char					*buffer;
	t_token					**tokens;
	t_token					*token;
	char					*str;
	t_type					last_token;
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
void						parse_error(t_parser *parser);
int							gen_token(t_parser *parser, t_mode mode);
int							is_special(int c);
int							is_dquote(int c);
int							is_quote(int c);
void						extract(t_parser *parser, int *index,
								int (*ctrl)(int), t_mode mode);
void						join_last(t_parser *parser);
char						*if_double(char *str, int *index, char *twice,
								char *once);
void						count_parentesis(int *parentesis, t_token *token);

t_token						*parse_line(t_token **tokens);
void						parse_cmd(t_token *token, t_token **root,
								t_token **last);
void						parse_pipe(t_token *token, t_token **root,
								t_token **last);
void						parse_redirect(t_token **tokens, int *i,
								t_token **root, t_token **last);
void						parse_open(t_token **tokens, int *i, t_token **root,
								t_token **last);
// Expand

char						*expand_var(char *str);
char						**expand_wildcard(char *pattern);
void						remove_quotes(char *str);
int							check_quotes(int c, int *in_quote);
char						**get_files(int hidden);
int							match_wildcard(char *pattern, char *filename,
								int in_quote);

// Debug

char						*get_enum(t_type type);
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
char						*extract_before_dollar(char *ptr);
char						*extract_after_dollar(char *ptr);
char						*ft_strjoin_with(char *s1, char *s2, char *c);
char						*extract_var(char *ptr);
char						*safe_join(char *s1, char *s2);



// Execute

char						*pathfinder(const char *cmd, char **env);
int         execute_cmd(char **args, t_data *data);
void executor(t_data *data, t_token *root);
// Executor utils


void handle_basic_cmd(t_data *data, t_token *root);
void handle_pipe(t_data *data, t_token *root);
void handle_and_operator(t_data *data, t_token *root);
void handle_or_operator(t_data *data, t_token *root);
void redirects(t_data *data, t_token *root);

// void	handle_redirects(t_token *root);
// void handle_redirect_heredoc(t_data * data,t_token *root);
void handle_redirect_append(t_data *data,t_token *root, int *fd);
void handle_redirect_output(t_data *data, t_token *root, int *fd);
void handle_redirect_input(t_data *data, t_token *root, int *fd);

void	custom_dup2(int fd, char *flag);
void	custom_pipe(int fds[2]);
// void	check_fork(pid_t pid, int wefd, int refd);
void	close_fds(int wefd, int refd);
void	custom_unlink(char *filepath);
char	**fill_args_array(t_token *cmd, t_data *data);

// Built in Utils

int							check_exit_value(char *str);
int							count_tokens(t_token **token);
int							is_builtin(char **args, t_data *data);
void						print_string_array(char **strs);
int							is_valid_identifier(char *str);
int							find_eq_i(char *str);
int							var_exists(char **env, char *to_check);
void						free_previous_sorted_exp(char **exported_dup,
								int i);
void						value_checker(char **sorted_exp, int i);
char						*strdup_and_add_quotes(char *str);
char						**export_strsdup(char **strs);
int							replace_existing_var(char **env, char *to_check);
int							var_replace(char **env, char *to_check);
int							is_there_char(char *str, char c);
int							check_var_existence(char **env, char *ptr);
int							check_equal(char *ptr);
int							iterate_vars(t_data *data, char **new_env, int i,
								int token_count);
// Pathfinder
char						*pathfinder(const char *cmd, char **env);

// Built in

void						custom_echo(char **args);
void						clean_exit(t_data *data, char **args);
void						custom_pwd(void);
void						custom_chdir(char **args);
void						custom_env(t_data *data);
void						custom_export(t_data *data, char **args);
void						custom_unset(t_data *data, char **args);

// Utils

int							print_error(char *msg);
int							print_error1(char *msg, char *msg1);
int							print_error2(char *msg, char *msg1, char *msg2);
int							print_error3(char *msg, char *msg1, char *msg2,
								char *msg3);

#endif // !
