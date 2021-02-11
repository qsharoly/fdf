/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_dtoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:45:44 by qsharoly          #+#    #+#             */
/*   Updated: 2021/02/11 12:58:19 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"

char		*ft_mini_dtoa(double a)
{
	char		*s;
	char		*intstr;
	char		*fracstr;
	int			i_len;
	int			f_len;

	intstr = ft_itoa(fabs(trunc(a)));
	fracstr = ft_itoa(fabs(a - trunc(a)) * 1000);
	i_len = ft_strlen(intstr);
	f_len = ft_strlen(fracstr);
	s = malloc(sizeof(*s) * (1 + i_len + 1 + f_len + 1));
	if (s == NULL)
		return (NULL);
	*s = a < 0 ? '-' : ' ';
	ft_memcpy(s + 1, intstr, i_len);
	*(s + 1 + i_len) = '.';
	ft_memcpy(s + 1 + i_len + 1, fracstr, f_len);
	*(s + 1 + i_len + 1 + f_len) = '\0';
	free(intstr);
	free(fracstr);
	return (s);
}
