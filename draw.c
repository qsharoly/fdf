/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:26:50 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/24 18:51:32 by qsharoly         ###   ########.fr       */
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

int		inbounds(t_float2 point, t_bitmap *bmp)
{
	return (point.x >= 0.0 && point.x <= bmp->x_dim
			&& point.y >= 0.0 && point.y <= bmp->y_dim);
}

void	draw_line(t_bitmap *bmp, t_float2 a, t_float2 b, t_rgba color)
{
	t_float2	p;
	t_float2	step;
	float		dt;
	float		t;

	p = a;
	dt = 1 / distance(a, b);
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

void	draw_edge(t_view view, t_float3 a, t_float3 b, t_rgba color)
{
	t_float2	aa;
	t_float2	bb;

	aa = take_xy(project(a, view.cam, view.bmp));
	bb = take_xy(project(b, view.cam, view.bmp));
	draw_line(view.bmp, aa, bb, color);
}

void	draw_line_gradient(t_bitmap *bmp, t_vertex a, t_vertex b)
{
	t_float3	p;
	t_float3	step;
	float		dt;
	float		t;

	p = a.vec;
	dt = 1 / distance(take_xy(a.vec), take_xy(b.vec));
	step.x = (b.vec.x - a.vec.x) * dt;
	step.y = (b.vec.y - a.vec.y) * dt;
	step.z = (b.vec.z - a.vec.z) * dt;
	t = 0;
	while (t < 1)
	{
		if (inbounds(take_xy(p), bmp))
			set_pixel(bmp, p.x, p.y, mix(a.col, b.col, 1 - t));
		t += dt;
		p = add_float3(p, step);
	}
}
