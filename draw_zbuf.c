/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_zbuf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:26:50 by qsharoly          #+#    #+#             */
/*   Updated: 2021/02/11 15:31:13 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "palette.h"

void			reset_zbuf(t_cam *cam)
{
	t_uint		i;

	i = 0;
	while (i < cam->zbuf_size)
	{
		cam->zbuf[i] = INFINITY;
		i++;
	}
}

static float	get_zbuf(t_cam *cam, t_uint x, t_uint y)
{
	return (*(cam->zbuf + y * cam->zbuf_stride + x));
}

static void		set_zbuf(t_cam *cam, t_uint x, t_uint y, float val)
{
	*(cam->zbuf + y * cam->zbuf_stride + x) = val;
}

/*
**  use on projected vertices a and b
**	Implies that at the start of each frame
**	all elements of z_buf are set to +INFINITY
*/

void			draw_line_gradient_zbuf(t_bitmap bmp, t_cam *cam,
					t_vertex a, t_vertex b)
{
	t_vec3	p;
	t_vec3	step;
	float	dt;
	float	t;

	if (!inbounds3(a.vec, bmp, cam) && !inbounds3(b.vec, bmp, cam))
		return ;
	p = a.vec;
	if ((dt = 1 / length2(take_xy(a.vec), take_xy(b.vec))) < 0.0001)
		return ;
	step.x = (b.vec.x - a.vec.x) * dt;
	step.y = (b.vec.y - a.vec.y) * dt;
	step.z = (b.vec.z - a.vec.z) * dt;
	t = 0;
	while (t < 1)
	{
		if (inbounds(take_xy(p), bmp)
			&& p.z < get_zbuf(cam, p.x, p.y))
		{
			set_zbuf(cam, p.x, p.y, p.z);
			set_pixel(bmp, p.x, p.y, mix(a.col, b.col, 1 - t));
		}
		t += dt;
		p = add3(p, step);
	}
}
