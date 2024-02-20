/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:26:50 by qsharoly          #+#    #+#             */
/*   Updated: 2024/02/20 10:25:31 by kith             ###   ########.fr       */
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
	float altitude = a.altitude;
	float step_altitude = (b.altitude - a.altitude) * dt;
	t = 0;
	while (t < 1)
	{
		set_pixel(bmp, p.x, p.y, color_gradient(altitude, PURPLE, GRASS, PEACH));
		t += dt;
		p.x += step.x;
		p.y += step.y;
		altitude += step_altitude;
	}
}

int		get_pixel(t_bitmap bmp, int x, int y)
{
	int i = x + y * bmp.x_dim;
	return bmp.data[i];
}

void	set_pixel(t_bitmap bmp, int x, int y, int color)
{
	int i = x + y * bmp.x_dim;
	bmp.data[i] = color;
}

/*
**  use on projected vertices a and b
**	Implies that at the start of each frame
**	all elements of z_buf are set to -INFINITY
*/

void	line_gradient_zbuf(t_bitmap bmp, void *zbuf, t_vertex aa, t_vertex bb)
{
	float *zbuffer = zbuf;

    float dt1 = fabs(aa.x - bb.x);
    float dt2 = fabs(aa.y - bb.y);
    float distance = fmax(dt1, dt2);
	if (distance == 0)
		return ;

	float dx = (bb.x - aa.x)/distance;
	float dy = (bb.y - aa.y)/distance;
	float dz = (bb.z - aa.z)/distance;
	float dw = (bb.w - aa.w)/distance;
	int steps = distance + 1;
	for (int i = 0; i < steps; ++i)
	{
		int pixel = (int)aa.x + (int)aa.y * bmp.x_dim;
		if (aa.z > zbuffer[pixel])
		{
			zbuffer[pixel] = aa.z;
			bmp.data[pixel] = bmp.color_table[(int)((COLOR_TABLE_SIZE-1) * aa.w)];
		}
		aa.x += dx;
		aa.y += dy;
		aa.z += dz;
		aa.w += dw;
	}
}
