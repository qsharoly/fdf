/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbyte.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 10:18:15 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/07 10:46:40 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putbyte(char unsigned b)
{
	char unsigned	hi;
	char unsigned	lo;

	hi = b / 16;
	lo = b % 16;
	hi <= 9 ? ft_putchar('0' + hi) : ft_putchar('a' + hi - 9);
	lo <= 9 ? ft_putchar('0' + lo) : ft_putchar('a' + lo - 9);
}
