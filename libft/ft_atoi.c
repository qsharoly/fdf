/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:40:27 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/12 11:16:49 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	ft_isspace(char c)
{
	return (c == '\t' || c == '\v' || c == '\f'
			|| c == '\r' || c == '\n' || c == ' ');
}

static char	*skip_whitespace(char *p)
{
	while (ft_isspace(*p))
		p++;
	return (p);
}

static char	*skip_digits(char *p)
{
	while (ft_isdigit(*p))
		p++;
	return (p);
}

static long	atoi_with_overflow_detection(const char *start, const char *end,
		long sign_mul)
{
	long	nbr;
	long	digit;

	nbr = 0;
	while (start < end)
	{
		digit = (*start - '0');
		if (sign_mul > 0 ? nbr > LONG_MAX / 10 : -nbr < LONG_MIN / 10)
			return (sign_mul == 1 ? LONG_MAX : LONG_MIN);
		nbr = nbr * 10;
		if (sign_mul > 0 ? nbr > LONG_MAX - digit : -nbr < LONG_MIN + digit)
			return (sign_mul > 0 ? LONG_MAX : LONG_MIN);
		nbr += digit;
		start++;
	}
	return (nbr * sign_mul);
}

int			ft_atoi(const char *str)
{
	long	nbr;
	long	sign_mul;
	char	*start;
	char	*end;

	start = skip_whitespace((char *)str);
	sign_mul = 1;
	if (*start == '+')
		start++;
	else if (*start == '-')
	{
		sign_mul = -1;
		start++;
	}
	end = skip_digits(start);
	nbr = 0;
	if (end - start > 18)
		return ((int)atoi_with_overflow_detection(start, end, sign_mul));
	else
		while (start < end)
		{
			nbr = nbr * 10 + (*start - '0');
			start++;
		}
	return ((int)nbr * sign_mul);
}
