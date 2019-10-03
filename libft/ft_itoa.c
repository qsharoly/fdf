/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:18:53 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/11 18:11:33 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int		count;

	if (n == 0)
		return (1);
	count = 0;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static int	mypow(int nb, int pow)
{
	int		res;

	if (pow < 0)
		return (0);
	res = 1;
	while (pow > 0)
	{
		res *= nb;
		pow--;
	}
	return (res);
}

static void	itoa_simple_positive(char *s, int n, int digit_count)
{
	int		i;

	i = 0;
	while (i < digit_count)
	{
		s[i] = '0' + n / mypow(10, digit_count - i - 1) % 10;
		i++;
	}
}

char		*ft_itoa(int n)
{
	char	*a;
	int		digit_count;

	digit_count = count_digits(n);
	a = ft_strnew(digit_count + (n < 0 ? 1 : 0));
	if (a)
	{
		if (n == -2147483648)
		{
			ft_strcat(a, "-2");
			digit_count -= 1;
			n = 147483648;
		}
		if (n < 0)
		{
			a[0] = '-';
			n = -n;
		}
		itoa_simple_positive(ft_strchr(a, '\0'), n, digit_count);
	}
	return (a);
}
