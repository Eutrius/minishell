/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:03:18 by lonulli           #+#    #+#             */
/*   Updated: 2025/02/18 14:04:08 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	char	*buf;
	t_data	data;
	t_token	**tokens;

	(void)data;
	while (1)
	{
		buf = readline("B_Bros > ");
		add_history(buf);
		tokens = parse_cmd(buf);
		print_tokens(tokens);
		custom_echo(buf, tokens[0]->content);
		clean_exit(buf);
		custom_pwd(buf);
		custom_chdir(buf, tokens[0]->content);
		free(tokens);
		free(buf);
	}
	return (0);
}
