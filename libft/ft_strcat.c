/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 10:20:44 by qsharoly          #+#    #+#             */
/*   Updated: 2021/07/03 02:42:26 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, char const *s2)
{
	char	*cur;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	cur = s1 + ft_strlen(s1);
	while (*s2)
	{
		*cur = *s2;
		cur++;
		s2++;
	}
	*cur = '\0';
	return (s1);
}
