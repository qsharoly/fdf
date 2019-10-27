/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:45:10 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/27 15:06:42 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

void	ft_put_float(float a)
{
	ft_putnbr(floor(a));
	ft_putchar('.');
	ft_putnbr(floor((a - floor(a)) * 1000));
}
