/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 10:32:03 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/09 16:30:56 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, char const *s2, size_t n)
{
	char	*s1_terminator_pos;
	size_t	i;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	s1_terminator_pos = s1 + ft_strlen(s1);
	i = 0;
	while (*(s2 + i) && i < n)
	{
		*(s1_terminator_pos + i) = *(s2 + i);
		i++;
	}
	*(s1_terminator_pos + i) = '\0';
	return (s1);
}
