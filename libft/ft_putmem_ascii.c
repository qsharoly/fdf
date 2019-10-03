/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmem_ascii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 11:09:39 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/07 11:12:46 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putmem_ascii(const void *s, size_t n)
{
	size_t			i;
	char unsigned	c;

	i = 0;
	while (i < n)
	{
		c = *((char unsigned *)s + i);
		ft_isprint(c) ? ft_putchar(c) : ft_putchar('.');
		i++;
	}
}
