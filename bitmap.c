/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:18:39 by qsharoly          #+#    #+#             */
/*   Updated: 2021/07/22 15:05:45 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitmap.h"
#include <stdlib.h>

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
