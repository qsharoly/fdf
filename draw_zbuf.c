/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_zbuf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:26:50 by qsharoly          #+#    #+#             */
/*   Updated: 2021/07/03 01:10:28 by debby            ###   ########.fr       */
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
		cam->zbuf[i] = -INFINITY;
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

//TODO: correct z culling
int		inbounds3(t_vec3 point, t_bitmap bmp, const t_cam *cam)
{
	(void)cam;
	return (point.x >= 0.0 && point.x <= bmp.x_dim
			&& point.y >= 0.0 && point.y <= bmp.y_dim
			&& point.z <= 0);
}

/*
**  use on projected vertices a and b
**	Implies that at the start of each frame
**	all elements of z_buf are set to -INFINITY
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
	if ((dt = 1 / len2(a.vec.x, a.vec.y, b.vec.x, b.vec.y)) < 0.0001)
		return ;
	step.x = (b.vec.x - a.vec.x) * dt;
	step.y = (b.vec.y - a.vec.y) * dt;
	step.z = (b.vec.z - a.vec.z) * dt;
	t = 0;
	while (t < 1)
	{
		if (inbounds(p.x, p.y, bmp)//inbounds3(p, bmp, cam)
			&& p.z > get_zbuf(cam, p.x, p.y))
		{
			set_zbuf(cam, p.x, p.y, p.z);
			set_pixel(bmp, p.x, p.y, mix(a.color, b.color, 1 - t));
		}
		t += dt;
		p.x += step.x;
		p.y += step.y;
		p.z += step.z;
	}
}

void	line_dda_gradient_zbuf(t_bitmap bmp, t_cam *cam, t_vertex a, t_vertex b)
{
	float	x, y;
	float	dx, dy;
	float	step;
	float	z, dz;
	int		i;

	if (!inbounds3(a.vec, bmp, cam) && !inbounds3(b.vec, bmp, cam))
		return ;
	dx = b.vec.x - a.vec.x;
	dy = b.vec.y - a.vec.y;
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	dz = (b.vec.z - a.vec.z) / step;
	x = a.vec.x;
	y = a.vec.y;
	z = a.vec.z;
	i = 0;
	while (i <= step)
	{
		if (inbounds(x, y, bmp)//inbounds3(p, bmp, cam)
			&& z > get_zbuf(cam, x, y))
		{
			set_zbuf(cam, x, y, z);
			set_pixel(bmp, x, y, mix(a.color, b.color, (float)(step - i) / step));
		}
		x += dx;
		y += dy;
		z += dz;
		i++;
	}
}
