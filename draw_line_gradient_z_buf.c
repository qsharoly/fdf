/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:26:50 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/27 15:05:31 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "palette.h"

void			reset_z_buf(t_cam *cam)
{
	t_uint		i;

	i = 0;
	while (i < cam->z_buf_size)
	{
		cam->z_buf[i] = INFINITY;
		i++;
	}
}

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
**	all elements of z_buf are set to +INFINITY
*/

void			draw_line_gradient_z_buf(t_bitmap *bmp, t_cam *cam,
					t_vertex a, t_vertex b)
{
	t_float3	p;
	t_float3	step;
	float		dt;
	float		t;

	if (!inbounds3(a.vec, bmp, cam) && !inbounds3(b.vec, bmp, cam))
		return ;
	p = a.vec;
	if ((dt = 1 / distance(take_xy(a.vec), take_xy(b.vec))) < 0.0001)
		return ;
	step.x = (b.vec.x - a.vec.x) * dt;
	step.y = (b.vec.y - a.vec.y) * dt;
	step.z = (b.vec.z - a.vec.z) * dt;
	t = 0;
	while (t < 1)
	{
		if (inbounds3(p, bmp, cam)
			&& p.z < get_z_buf(cam, p.x, p.y))
		{
			set_z_buf(cam, p.x, p.y, p.z);
			set_pixel(bmp, p.x, p.y, mix(a.col, b.col, 1 - t));
		}
		t += dt;
		p = add_float3(p, step);
	}
}
