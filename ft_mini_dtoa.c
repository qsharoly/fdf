/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_dtoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:45:44 by qsharoly          #+#    #+#             */
/*   Updated: 2022/04/25 02:29:52 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"

static char	*ft_itoa_buf(char *buffer, int size, int n)
{
	int		neg = n < 0;
	char	*pos = buffer + size;

	if (n <= 0)
	{
		pos--;
		*pos = -(n % -10) + '0';
		n /= -10;
	}
	while (n)
	{
		pos--;
		*pos = n % 10 + '0';
		n /= 10;
	}
	if (neg)
	{
		pos--;
		*pos = '-';
	}
	return (pos);
}

char	*ft_mini_dtoa(char *buffer, int size, float a)
{
	char	buf[2][ITOA_BUF_SIZE];
	char	*intstr;
	char	*fracstr;
	int		i_len;
	int		f_len;

	intstr = ft_itoa_buf(buf[0], ITOA_BUF_SIZE, fabs(trunc(a)));
	fracstr = ft_itoa_buf(buf[1], ITOA_BUF_SIZE, fabs(a - trunc(a)) * 1000);
	i_len = buf[0] + ITOA_BUF_SIZE - intstr;
	f_len = buf[1] + ITOA_BUF_SIZE - fracstr;
	if (i_len + f_len + 3 > size)
		return (NULL);
	buffer[0] = a < 0 ? '-' : ' ';
	ft_memcpy(&buffer[1], intstr, i_len);
	buffer[i_len + 1] = '.';
	ft_memcpy(&buffer[i_len + 2], fracstr, f_len);
	buffer[i_len + 2 + f_len] = '\0';
	return (buffer);
}
