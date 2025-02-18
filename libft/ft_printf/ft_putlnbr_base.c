/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlnbr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:23:05 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/15 14:18:18 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stddef.h>

void	ft_putlnbr_base(unsigned long long num, char *base, int *count)
{
	size_t	base_len;

	base_len = ft_strlen(base);
	if (num >= base_len)
		ft_putlnbr_base(num / base_len, base, count);
	ft_putlchar(base[num % base_len], count, NULL);
}
