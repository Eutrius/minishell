/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:08:15 by lonulli           #+#    #+#             */
/*   Updated: 2025/02/18 14:08:16 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../includes/minishell.h"



int executor(t_token *token)
{
	if (token->type == FILENAME)
		printf("token is a file.\n");
	else
		printf("Is not a file.\n");
	return 0;
}

int main()
{
	t_token token;
	token.type = CMD;
	executor(&token);
}
