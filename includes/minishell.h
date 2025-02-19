/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:02:54 by lonulli           #+#    #+#             */
/*   Updated: 2025/02/18 14:02:57 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define NONEWLINE 'N'
# define NEWLINE 'n'

typedef struct s_data	t_data;
typedef struct s_token	t_token;

typedef enum e_type
{
	FILENAME,
	CMD,
	FLAG,
	OPERATOR,
	WILDCARD,
	VARIABLE,
	OTHERS,
}						t_type;

// General struct
typedef struct s_data
{
	char				**env;
	t_token				**cmd;

}						t_data;

// Token struct
typedef struct s_token
{
	void				*content;
	t_type				type;

}						t_token;

t_token					**parse_cmd(char *cmd);
char					*pathfinder(const char *cmd, char **env);
void					print_tokens(t_token **tokens);

// Built ins

void					custom_echo(char *buf, void *content);
void					clean_exit(char *buf);
void					custom_pwd(char *buf);
void					custom_chdir(char *buf, char *path);

#endif // !
