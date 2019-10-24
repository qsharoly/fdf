/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:26:50 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/24 18:06:47 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static float	get_z_buf(t_cam *cam, t_uint x, t_uint y)
{
	return (*(cam->z_buf + y * cam->z_buf_stride + x));
}

static void		set_z_buf(t_cam *cam, t_uint x, t_uint y, float val)
{
	*(cam->z_buf + y * cam->z_buf_stride + x) = val;
}

/*
**  use on projected vertices a and b
**	Implies that at the start of each frame
**	all elements of z_buf are set to -INFINITY
**	and the camera normal cam->dir sticks out of the screen
*/

void			draw_line_gradient_z_buf(t_bitmap *bmp, t_cam *cam,
					t_vertex a, t_vertex b)
{
	t_float3	p;
	t_float3	step;
	float		dt;
	float		t;

	p = a.vec;
	dt = 1 / distance(take_xy(a.vec), take_xy(b.vec));
	step.x = (b.vec.x - a.vec.x) * dt;
	step.y = (b.vec.y - a.vec.y) * dt;
	step.z = (b.vec.z - a.vec.z) * dt;
	t = 0;
	while (t < 1)
	{
		if (inbounds(take_xy(p), bmp)
			&& p.z > get_z_buf(cam, p.x, p.y))
		{
			set_z_buf(cam, p.x, p.y, p.z);
			set_pixel(bmp, p.x, p.y, mix(a.col, b.col, 1 - t));
		}
		t += dt;
		p = add_float3(p, step);
	}
}
