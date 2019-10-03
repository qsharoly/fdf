/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 20:13:47 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/06 20:52:36 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char unsigned *)dest = *(char unsigned *)src;
		if (*(char unsigned *)src == (char unsigned)c)
			return (dest + 1);
		dest++;
		src++;
		i++;
	}
	return (NULL);
}
