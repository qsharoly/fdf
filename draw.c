/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:26:50 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/15 14:09:49 by qsharoly         ###   ########.fr       */
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
	float		length;
	t_float2	p;
	float		dt;
	float		t;

	p = a;
	length = distance(a, b);
	dt = 1 / length;
	t = 0;
	while (t < 1)
	{
		if (inbounds(p, bmp))
			set_pixel(bmp, p.x, p.y, color);
		t += dt;
		p.x = a.x + t * (b.x - a.x);
		p.y = a.y + t * (b.y - a.y);
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

void	draw_edge_gradient(t_bitmap *bmp, t_cam *cam, t_vertex a, t_vertex b)
{
	t_float2	p;
	t_float2	aa;
	t_float2	bb;
	float		dt;
	float		t;

	aa = take_xy(project(a.vec, cam, bmp));
	bb = take_xy(project(b.vec, cam, bmp));
	p = aa;
	dt = 1 / distance(aa, bb);
	t = 0;
	while (t < 1)
	{
		if (inbounds(p, bmp))
			set_pixel(bmp, p.x, p.y, mix(a.col, b.col, 1 - t));
		t += dt;
		p.x = aa.x + t * (bb.x - aa.x);
		p.y = aa.y + t * (bb.y - aa.y);
	}
}
