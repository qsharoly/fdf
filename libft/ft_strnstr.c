/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:33:16 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/11 13:24:03 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;
	char	*haystack_trim;

	if (haystack == NULL && needle == NULL)
		return (NULL);
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	haystack_trim = (char *)malloc(sizeof(char) + 1);
	ft_strncpy(haystack_trim, haystack, len);
	haystack_trim[len] = '\0';
	i = 0;
	while (haystack_trim[i])
	{
		if (ft_memcmp(&haystack_trim[i], needle, needle_len) == 0)
		{
			free(haystack_trim);
			return ((char *)&haystack[i]);
		}
		i++;
	}
	free(haystack_trim);
	return (NULL);
}
