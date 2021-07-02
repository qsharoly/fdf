/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:18:39 by qsharoly          #+#    #+#             */
/*   Updated: 2021/06/30 18:56:54 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitmap.h"
#include <stdlib.h>

t_uint	rgba_to_int(t_argb color)
{
	int	out;

	out = color.a << 24;
	out += color.r << 16;
	out += color.g << 8;
	out += color.b << 0;
	return (out);
}

t_argb	int_to_rgba(int color)
{
	t_argb			argb;

	argb.a = (color & 0xff000000) >> 24;
	argb.r = (color & 0x00ff0000) >> 16;
	argb.g = (color & 0x0000ff00) >> 8;
	argb.b = (color & 0x000000ff) >> 0;
	return (argb);
}

int		get_pixel(t_bitmap bmp, t_uint x, t_uint y)
{
	return (*(bmp.data + x + y * bmp.x_dim));
}

void	set_pixel(t_bitmap bmp, t_uint x, t_uint y, int color)
{
	*(bmp.data + x + y * bmp.x_dim) = color;
}

void	fill_rect(t_bitmap bmp, t_rect rect, int color)
{
	t_uint i;
	t_uint j;

	j = 0;
	while (j < rect.height)
	{
		i = 0;
		while (i < rect.width)
		{
			set_pixel(bmp, rect.x + i, rect.y + j, color);
			i++;
		}
		j++;
	}
}
