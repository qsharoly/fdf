/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:36:31 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/11 15:51:58 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int		ft_strncmp(char const *s1, char const *s2, size_t n)
{
	size_t	count;
	int		diff;

	if (n == 0)
		return (0);
	count = 0;
	diff = (unsigned char)*s1 - (unsigned char)*s2;
	while ((count < n) && (*s1 || *s2))
	{
		count++;
		diff = (unsigned char)*s1 - (unsigned char)*s2;
		if (diff != 0)
			break ;
		else
		{
			s1++;
			s2++;
		}
	}
	return (diff);
}
