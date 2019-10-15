/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:26:50 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/15 16:38:46 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

/*
**	Implies that at the start of each frame
**	all elements of z_buf are set to -INFINITY
**	and the camera normal cam->dir sticks out of the screen
*/

void	draw_edge_gradient_z_buf(t_bitmap *bmp, t_cam *cam,
		t_vertex a, t_vertex b)
{
	t_float3	p;
	float		dt;
	float		t;

	a.vec = project(a.vec, cam, bmp);
	b.vec = project(b.vec, cam, bmp);
	p = a.vec;
	dt = 1 / distance(take_xy(a.vec), take_xy(b.vec));
	t = 0;
	while (t < 1)
	{
		if (inbounds(take_xy(p), bmp))
		{
			if (p.z > *(cam->z_buf + (t_uint)p.y * bmp->x_dim + (t_uint)p.x))
			{
				*(cam->z_buf + (t_uint)p.y * bmp->x_dim + (t_uint)p.x) = p.z;
				set_pixel(bmp, p.x, p.y, mix(a.col, b.col, 1 - t));
			}
		}
		t += dt;
		p.x = a.vec.x + t * (b.vec.x - a.vec.x);
		p.y = a.vec.y + t * (b.vec.y - a.vec.y);
	}
}
