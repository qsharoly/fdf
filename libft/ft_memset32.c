/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset32.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 18:41:00 by qsharoly          #+#    #+#             */
/*   Updated: 2022/04/28 18:40:48 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero32(void *bb, size_t len)
{
	int	*b = bb;
	while (len)
	{
		*b++ = 0;
		len--;
	}
	return (bb);
}

void	*ft_memset32(void *bb, int c, size_t len)
{
	int		*b = bb;
	while (len)
	{
		*b++ = c;
		len--;
	}
	return (bb);
}

void	*ft_memset32f(void *bb, float c, size_t len)
{
	float	*b = bb;
	while (len)
	{
		*b++ = c;
		len--;
	}
	return (bb);
}
