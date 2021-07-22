/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:26:50 by qsharoly          #+#    #+#             */
/*   Updated: 2021/07/22 15:11:05 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "color.h"

int		inbounds(float x, float y, t_bitmap bmp)
{
	return (x >= 0.0 && x <= bmp.x_dim
			&& y >= 0.0 && y <= bmp.y_dim);
}

void	line_solid(t_bitmap bmp, t_vec3 a, t_vec3 b, int color)
{
	t_vec2	p;
	t_vec2	step;
	float		dt;
	float		t;

	p.x = a.x;
	p.y = a.y;
	dt = 1 / len2(a.x, a.y, b.x, b.y);
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

void	line_gradient(t_bitmap bmp, t_cam *cam, t_vertex a, t_vertex b)
{
	t_vec3	p;
	t_vec3	step;
	float	dt;
	float	t;

	if (!inbounds3(a.vec, bmp, cam) && !inbounds3(b.vec, bmp, cam))
		return ;
	p = a.vec;
	dt = 1 / len2(a.vec.x, a.vec.y, b.vec.x, b.vec.y);
	step.x = (b.vec.x - a.vec.x) * dt;
	step.y = (b.vec.y - a.vec.y) * dt;
	step.z = (b.vec.z - a.vec.z) * dt;
	t = 0;
	while (t < 1)
	{
		if (inbounds3(p, bmp, cam))
			set_pixel(bmp, p.x, p.y, mix(a.color, b.color, t));
		t += dt;
		p = add3(p, step);
	}
}
