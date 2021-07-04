/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:26:50 by qsharoly          #+#    #+#             */
/*   Updated: 2021/07/03 02:35:01 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

#define GETA(x) ((x & 0xff000000) >> 24)
#define GETR(x) ((x & 0x00ff0000) >> 16)
#define GETG(x) ((x & 0x0000ff00) >> 8)
#define GETB(x) ((x & 0x000000ff))

// mix: interpolate between colors
// ratio is expected to be in range [0.0, 1.0]
int	mix(int a, int b, float ratio)
{
	t_argb	color;

	color.a = GETA(a) * ratio + GETB(b) * (1 - ratio);
	color.r = sqrt(squared(GETR(a)) * ratio + squared(GETR(b)) * (1 - ratio));
	color.g = sqrt(squared(GETG(a)) * ratio + squared(GETG(b)) * (1 - ratio));
	color.b = sqrt(squared(GETB(a)) * ratio + squared(GETB(b)) * (1 - ratio));
	return (rgba_to_int(color));
}

/*
int lerp(int a, int b, float ratio)
{
	t_argb	color;

	color.a = GETA(a) * ratio + GETB(b) * (1 - ratio);
	color.r = GETR(a) * ratio + GETR(b) * (1 - ratio);
	color.b = GETB(a) * ratio + GETB(b) * (1 - ratio);
	color.g = GETG(a) * ratio + GETG(b) * (1 - ratio);
	return (rgba_to_int(color));
}
*/

int		inbounds(float x, float y, t_bitmap bmp)
{
	return (x >= 0.0 && x <= bmp.x_dim
			&& y >= 0.0 && y <= bmp.y_dim);
}

void	draw_line(t_bitmap bmp, t_vec3 a, t_vec3 b, int color)
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

void	draw_line_gradient(t_bitmap bmp, t_cam *cam, t_vertex a, t_vertex b)
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
			set_pixel(bmp, p.x, p.y, mix(a.color, b.color, 1 - t));
		t += dt;
		p = add3(p, step);
	}
}
