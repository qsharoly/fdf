/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 20:46:51 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/11 15:38:39 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*fresh;

	fresh = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (fresh)
	{
		ft_strcpy(fresh, s1);
		ft_strcat(fresh, s2);
	}
	return (fresh);
}
