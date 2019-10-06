/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:18:39 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/06 13:21:30 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitmap.h"
#include <stdlib.h>

t_uint	rgba_to_int(t_rgba color)
{
	t_uint	out;

	out = 0;
	out += color.r << 16;
	out += color.g << 8;
	out += color.b << 0;
	return (out);
}

t_rgba	int_to_rgba(int color)
{
	t_rgba	rgba;

	rgba.r = *((char *)&color + 2);
	rgba.g = *((char *)&color + 1);
	rgba.b = *((char *)&color + 0);
	rgba.a = *((char *)&color + 3);
	return (rgba);
}

t_rgba	get_pixel(t_bitmap *bmp, t_uint x, t_uint y)
{
	unsigned int		color;

	color = *(bmp->data + x + y * bmp->x_dim);
	return (int_to_rgba(color));
}

void	set_pixel(t_bitmap *bmp, t_uint x, t_uint y, t_rgba color)
{
	*(bmp->data + x + y * bmp->x_dim) = rgba_to_int(color);
}

void	fill_rect(t_bitmap *bmp, t_rect rect, t_rgba color)
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
