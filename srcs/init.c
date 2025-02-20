/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:41:47 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/20 17:42:01 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

void	init(t_data *data, t_operators *operators)
{
	data->operators = operators;
	init_operators(operators);
}

void	init_operators(t_operators *operators)
{
	ft_memcpy(operators->pipe, "|", 2);
	ft_memcpy(operators->r_in, "<", 2);
	ft_memcpy(operators->r_out, ">", 2);
	ft_memcpy(operators->cmd_and, "&&", 3);
	ft_memcpy(operators->cmd_or, "||", 3);
	ft_memcpy(operators->here_doc, "<<", 3);
	ft_memcpy(operators->append, ">>", 3);
}
