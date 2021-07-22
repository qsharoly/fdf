/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_zbuf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:26:50 by qsharoly          #+#    #+#             */
/*   Updated: 2021/07/22 18:42:20 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "color.h"

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

void	line_gradient_zbuf(t_bitmap bmp, t_cam *cam, t_vertex a, t_vertex b)
{
	t_vec3	p;
	t_vec3	step;
	float	dt;
	float	t;

	if (!inbounds3(a.vec, bmp, cam) && !inbounds3(b.vec, bmp, cam))
		return ;
	p = a.vec;
	if ((dt = 1 / fmax(fabs(a.vec.x - b.vec.x), fabs(a.vec.y - b.vec.y))) < 0.0001)
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
			set_pixel(bmp, p.x, p.y, mix(a.color, b.color, t));
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
			set_pixel(bmp, x, y, mix(a.color, b.color, i / step));
		}
		x += dx;
		y += dy;
		z += dz;
		i++;
	}
}

void	line_bresenham(t_bitmap bmp, t_cam *cam, t_vertex a, t_vertex b)
{
	int	x = a.vec.x, y = a.vec.y;
	int	x1 = b.vec.x, y1 = b.vec.y;
	int dx = fabs(x - x1);
	int dy = -fabs(y - y1);
	int sx = x < x1 ? 1 : -1;
	int sy = y < y1 ? 1 : -1;
	int	err = dx + dy, e2;
	float dz = (b.vec.z - a.vec.z);
	float sz = dz / fmax(dx, -dy);
	float z = a.vec.z;
	float t = 0, st = 1 / fmax(dx, -dy);
	while (1)
	{
		(void)cam;
		if (inbounds(x, y, bmp) && z > get_zbuf(cam, x, y))
		{
			set_zbuf(cam, x, y, z);
			set_pixel(bmp, x, y, mix(a.color, b.color, t));
		}
		e2 = 2*err;
		if (e2 >= dy)
		{
			if (x == x1) break;
			err += dy;
			x += sx;
		}
		if (e2 <= dx)
		{
			if (y == y1) break;
			err += dx;
			y += sy;
		}
		z += sz;
		t += st;
	}
}
