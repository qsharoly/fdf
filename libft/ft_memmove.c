/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 13:10:25 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/09 16:38:24 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t			i;
	char unsigned	src_char;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (((size_t)dest - (size_t)src) < len)
	{
		i = len;
		while (i > 0)
		{
			src_char = *((char unsigned *)(src + i - 1));
			*((char unsigned *)(dest + i - 1)) = src_char;
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			*((char unsigned *)(dest + i)) = *((char unsigned *)(src + i));
			i++;
		}
	}
	return (dest);
}
