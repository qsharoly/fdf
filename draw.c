/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:26:50 by qsharoly          #+#    #+#             */
/*   Updated: 2022/04/12 13:20:00 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "color.h"

int		inbounds(float x, float y, t_bitmap bmp)
{
	return (0.0 <= x && x <= bmp.x_dim
			&& 0.0 <= y && y <= bmp.y_dim);
}

void	line_solid(t_bitmap bmp, t_vec3 a, t_vec3 b, int color)
{
	t_vec2	p;
	t_vec2	step;
	float	dt;
	float	t;

	p.x = a.x;
	p.y = a.y;
	dt = 1 / fmax(fabs(a.x - b.x), fabs(a.y - b.y));
	if (dt < 0.00001)
		return ;
	step.x = (b.x - a.x) * dt;
	step.y = (b.y - a.y) * dt;
	t = 0;
	while (t < 1)
	{
		if (inbounds(p.x, p.y, bmp))
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
	if (!inbounds(a.vec.z, a.vec.y, bmp) && !inbounds(b.vec.x, b.vec.y, bmp))
		return ;
	p = a.vec;
	dt = 1 / fmax(fabs(a.vec.x - b.vec.x), fabs(a.vec.y - b.vec.y));
	step.x = (b.vec.x - a.vec.x) * dt;
	step.y = (b.vec.y - a.vec.y) * dt;
	step.z = (b.vec.z - a.vec.z) * dt;
	int	color_index = a.color_id;
	int color_step = (b.color_id - a.color_id) * dt;
	t = 0;
	while (t < 1)
	{
		if (inbounds(p.x, p.y, bmp))
			set_pixel(bmp, p.x, p.y, bmp.color_table[color_index]);
		color_index += color_step;
		t += dt;
		p = add3(p, step);
	}
}
