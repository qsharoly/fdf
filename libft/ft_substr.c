/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 20:38:36 by qsharoly          #+#    #+#             */
/*   Updated: 2021/07/03 07:17:25 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*fresh;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	fresh = ft_strnew(len);
	if (!fresh)
		return (NULL);
	ft_strncpy(fresh, s + start, len);
	return (fresh);
}
