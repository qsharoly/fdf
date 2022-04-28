/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:26:50 by qsharoly          #+#    #+#             */
/*   Updated: 2022/04/28 19:57:43 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "color.h"

void	line_solid(t_bitmap bmp, t_vec3 a, t_vec3 b, int color)
{
	t_vec3	p;
	t_vec3	step;
	float	dt;
	float	t;

	p = a;
	dt = 1 / fmax(fabs(a.x - b.x), fabs(a.y - b.y));
	if (dt < 0.00001)
		return ;
	step.x = (b.x - a.x) * dt;
	step.y = (b.y - a.y) * dt;
	t = 0;
	while (t < 1)
	{
		if (is_inside(p, bmp.x_dim, bmp.y_dim))
			set_pixel(bmp, p.x, p.y, color);
		t += dt;
		p.x += step.x;
		p.y += step.y;
	}
}

void	line_gradient(t_bitmap bmp, void *user, t_vertex a, t_vertex b)
{
	t_vec3	p;
	t_vec3	step;
	float	dt;
	float	t;

	(void)user;
	p = a.vec;
	dt = fmax(fabs(a.vec.x - b.vec.x), fabs(a.vec.y - b.vec.y));
	if (dt == 0)
		return ;
	dt = 1/dt;
	step.x = (b.vec.x - a.vec.x) * dt;
	step.y = (b.vec.y - a.vec.y) * dt;
	int	color_index = a.color_id;
	int color_step = (b.color_id - a.color_id) * dt;
	t = 0;
	while (t < 1)
	{
		set_pixel(bmp, p.x, p.y, bmp.color_table[color_index]);
		color_index += color_step;
		t += dt;
		p.x += step.x;
		p.y += step.y;
	}
}

static float	get_zbuf(t_zbuffer *zbuf, int x, int y)
{
	return (zbuf->z[x + y * zbuf->stride]);
}

static void		set_zbuf(t_zbuffer *zbuf, int x, int y, float val)
{
	zbuf->z[x + y * zbuf->stride] = val;
}

int		get_pixel(t_bitmap bmp, int x, int y)
{
	return (*(bmp.data + x + y * bmp.x_dim));
}

void	set_pixel(t_bitmap bmp, int x, int y, int color)
{
	*(bmp.data + x + y * bmp.x_dim) = color;
}

/*
**  use on projected vertices a and b
**	Implies that at the start of each frame
**	all elements of z_buf are set to -INFINITY
*/

void	line_gradient_zbuf(t_bitmap bmp, void *zbuffer, t_vertex a, t_vertex b)
{
	t_vec3	p;
	t_vec3	step;
	float	dt;
	float	t;

	p = a.vec;
	dt = fmax(fabs(a.vec.x - b.vec.x), fabs(a.vec.y - b.vec.y));
	if (dt == 0)
		return ;
	dt = 1/dt;
	step.x = (b.vec.x - a.vec.x) * dt;
	step.y = (b.vec.y - a.vec.y) * dt;
	step.z = (b.vec.z - a.vec.z) * dt;
	int	color_index = a.color_id;
	int color_step = (b.color_id - a.color_id) * dt;
	t = 0;
	while (t < 1)
	{
		if (p.z > get_zbuf(zbuffer, p.x, p.y))
		{
			set_zbuf(zbuffer, p.x, p.y, p.z);
			set_pixel(bmp, p.x, p.y, bmp.color_table[color_index]);
		}
		t += dt;
		p.x += step.x;
		p.y += step.y;
		p.z += step.z;
		color_index += color_step;
	}
}
