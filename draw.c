/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:26:50 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/27 15:05:19 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

/*
** mix: interpolate between colors
** ratio is expected to be in range [0.0, 1.0]
*/

t_rgba	mix(t_rgba col1, t_rgba col2, float ratio)
{
	t_rgba	color;

	color.r = sqrt(squared(col1.r) * ratio + squared(col2.r) * (1 - ratio));
	color.g = sqrt(squared(col1.g) * ratio + squared(col2.g) * (1 - ratio));
	color.b = sqrt(squared(col1.b) * ratio + squared(col2.b) * (1 - ratio));
	return (color);
}

int		inbounds(t_vec2 point, t_bitmap bmp)
{
	return (point.x >= 0.0 && point.x <= bmp.x_dim
			&& point.y >= 0.0 && point.y <= bmp.y_dim);
}

int		inbounds3(t_vec3 point, t_bitmap bmp, const t_cam *cam)
{
	return (point.x >= 0.0 && point.x <= bmp.x_dim
			&& point.y >= 0.0 && point.y <= bmp.y_dim
			&& point.z >= cam->z_near && point.z <= cam->z_far);
}

void	draw_line(t_bitmap bmp, t_vec2 a, t_vec2 b, t_rgba color)
{
	t_vec2	p;
	t_vec2	step;
	float		dt;
	float		t;

	p = a;
	dt = 1 / length2(a, b);
	if (dt < 0.00001)
		return ;
	step.x = (b.x - a.x) * dt;
	step.y = (b.y - a.y) * dt;
	t = 0;
	while (t < 1)
	{
		if (inbounds(p, bmp))
			set_pixel(bmp, p.x, p.y, color);
		t += dt;
		p.x += step.x;
		p.y += step.y;
	}
}

void	draw_line_gradient(t_bitmap bmp, t_cam *cam, t_vertex a, t_vertex b)
{
	t_vec3	p;
	t_vec3	step;
	float	dt;
	float	t;

	if (!inbounds3(a.vec, bmp, cam) && !inbounds3(b.vec, bmp, cam))
		return ;
	p = a.vec;
	dt = 1 / length2(take_xy(a.vec), take_xy(b.vec));
	step.x = (b.vec.x - a.vec.x) * dt;
	step.y = (b.vec.y - a.vec.y) * dt;
	step.z = (b.vec.z - a.vec.z) * dt;
	t = 0;
	while (t < 1)
	{
		if (inbounds3(p, bmp, cam))
			set_pixel(bmp, p.x, p.y, mix(a.col, b.col, 1 - t));
		t += dt;
		p = add_vec3(p, step);
	}
}
