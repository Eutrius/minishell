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

typedef struct s_data	t_data;
typedef struct s_token	t_token;

typedef enum e_type
{
	FILENAME,
	CMD,
	FLAG,
	OPERATOR,
	WILDCARD,
}						t_type;

// General struct
typedef struct s_data
{
	char				**env;

}						t_data;

// Token struct
typedef struct s_token
{
	void				*content;
	t_type				type;

}						t_token;
#endif // !
