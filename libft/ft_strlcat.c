/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 10:40:57 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/09 16:31:34 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char const *src, size_t size)
{
	char	*dst_end;
	char	dst_initial_len;
	size_t	i;

	i = 0;
	while (i < size && dst[i])
		i++;
	dst_end = dst + i;
	dst_initial_len = i;
	i = 0;
	while (src[i] && i + dst_initial_len + 1 < size)
	{
		dst_end[i] = src[i];
		i++;
	}
	if (i + dst_initial_len < size)
		dst_end[i] = '\0';
	return (dst_initial_len + ft_strlen(src));
}
