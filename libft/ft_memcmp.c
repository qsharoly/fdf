/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 21:12:16 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/07 09:23:22 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int		diff;
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		diff = *((unsigned char *)s1) - *((unsigned char *)s2);
		if (diff != 0)
			break ;
		else
		{
			s1++;
			s2++;
			i++;
		}
	}
	return (diff);
}
