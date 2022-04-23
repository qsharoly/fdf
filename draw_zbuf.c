/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_zbuf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:26:50 by qsharoly          #+#    #+#             */
/*   Updated: 2022/04/23 20:47:29 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "color.h"

void			reset_zbuf(t_zbuffer *zbuf)
{
	int		i;

	i = 0;
	while (i < zbuf->size)
	{
		zbuf->z[i] = -INFINITY;
		i++;
	}
}

static float	get_zbuf(t_zbuffer *zbuf, t_uint x, t_uint y)
{
	return (zbuf->z[x + y * zbuf->stride]);
}

static void		set_zbuf(t_zbuffer *zbuf, t_uint x, t_uint y, float val)
{
	zbuf->z[x + y * zbuf->stride] = val;
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
	if ((dt = 1 / fmax(fabs(a.vec.x - b.vec.x), fabs(a.vec.y - b.vec.y))) < 0.0001)
		return ;
	step.x = (b.vec.x - a.vec.x) * dt;
	step.y = (b.vec.y - a.vec.y) * dt;
	step.z = (b.vec.z - a.vec.z) * dt;
	int	color_index = a.color_id;
	int color_step = (b.color_id - a.color_id) * dt;
	t = 0;
	while (t < 1)
	{
		if (inbounds(p.x, p.y, bmp)
				&& p.z > get_zbuf(zbuffer, p.x, p.y))
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

void	line_gradient_zbuf_bigzoom_clamp(t_bitmap bmp, void *zbuffer, t_vertex a, t_vertex b)
{
	t_vec3	p;
	t_vec3	step;
	float	dt;
	float	t;

	if (!inbounds(a.vec.x, a.vec.y, bmp) && !inbounds(b.vec.x, b.vec.y, bmp))
		return ;
	p = a.vec;
	if ((dt = 1 / fmax(fabs(a.vec.x - b.vec.x), fabs(a.vec.y - b.vec.y))) < 0.0001)
		return ;
	step.x = (b.vec.x - a.vec.x) * dt;
	step.y = (b.vec.y - a.vec.y) * dt;
	step.z = (b.vec.z - a.vec.z) * dt;
	int	color_index = a.color_id;
	int color_step = (b.color_id - a.color_id) * dt;
	t = 0;
	while (t < 1)
	{
		if (inbounds(p.x, p.y, bmp)
				&& p.z > get_zbuf(zbuffer, p.x, p.y))
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
