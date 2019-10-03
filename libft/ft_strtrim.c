/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 20:53:32 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/11 15:44:40 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_white_space(char c)
{
	return (c == '\t' || c == '\v' || c == '\f'
			|| c == '\r' || c == '\n' || c == ' ');
}

char		*ft_strtrim(char const *s)
{
	char	*result;
	char	*from;
	char	*till;

	from = (char *)s;
	while (ft_is_white_space(*from))
		from++;
	till = (char *)&s[ft_strlen(s) - 1];
	while (ft_is_white_space(*till))
		till--;
	till += 1;
	if (till <= from)
		result = ft_strdup("");
	else
		result = ft_strsub(from, 0, till - from);
	return (result);
}
