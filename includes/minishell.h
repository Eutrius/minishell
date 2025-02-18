#ifndef MINISHELL_H 
# define MINISHELL_H

typedef enum e_type t_type;
typedef struct  s_data t_data;
typedef struct s_token t_token;

//General struct
typedef struct s_data
{
	char **env;

}	t_data;


//Token struct
typedef struct s_token
{
	void *content;
	t_type type;

}	t_token;

typedef enum e_type
{
	CMD,
	FLAG,
	FILE,
	OPERATOR,
	WILDCARD,
} t_type;

#endif // !
