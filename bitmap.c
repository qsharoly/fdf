/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:18:39 by qsharoly          #+#    #+#             */
/*   Updated: 2022/04/24 14:05:28 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitmap.h"

int		get_pixel(t_bitmap bmp, t_uint x, t_uint y)
{
	return (*(bmp.data + x + y * bmp.x_dim));
}

void	set_pixel(t_bitmap bmp, t_uint x, t_uint y, int color)
{
	*(bmp.data + x + y * bmp.x_dim) = color;
}
