/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:21:01 by jyriarte          #+#    #+#             */
/*   Updated: 2025/02/22 11:27:05 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	print_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	print_error1(char *msg, char *msg1)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(msg1, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	print_error2(char *msg, char *msg1, char *msg2)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(msg1, 2);
	ft_putstr_fd(msg2, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
