/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:45:44 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/29 18:56:17 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

char	*ft_itoa_float(float a)
{
	char	*s;
	char	*s1;
	char	*s2;
	float	ipart;

	ipart = trunc(a);
	s = ft_itoa(ipart);
	s1 = ft_strjoin(s, ".");
	free(s);
	s = ft_itoa(trunc((a - ipart) * 1000));
	s2 = ft_strjoin(s1, s);
	free(s);
	free(s1);
	return (s2);
}
