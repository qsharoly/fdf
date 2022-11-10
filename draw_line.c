/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:26:50 by qsharoly          #+#    #+#             */
/*   Updated: 2022/11/07 21:40:44 by kith             ###   ########.fr       */
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

/*
static float	get_zbuf(t_zbuffer *zbuf, int x, int y)
{
	return (zbuf->z[x + y * zbuf->stride]);
}

static void		set_zbuf(t_zbuffer *zbuf, int x, int y, float val)
{
	zbuf->z[x + y * zbuf->stride] = val;
}
*/

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

#include <xmmintrin.h>
#include <stdalign.h>
/*
#include <stdio.h>
void echo_ps(char *label, __m128 a)
{
	alignas(16) float f[4];
	_mm_store_ps(f, a);
	printf("%s=[%f, %f, %f, %f]\n", label, f[0], f[1], f[2], f[3]);
}

void echo_epi32(char *label, __m128i a)
{
	alignas(16) int i[4];
	_mm_store_si128((__m128i *)i, a);
	printf("%s=[%02x, %02x, %02x, %02x]\n", label, i[0], i[1], i[2], i[3]);
}
*/

void	line_gradient_zbuf(t_bitmap bmp, void *zbuffer, t_vertex aa, t_vertex bb)
{
    float dt1 = fabs(aa.x - bb.x);
    float dt2 = fabs(aa.y - bb.y);
    float dt = dt1 > dt2 ? dt1 : dt2;
	if (dt == 0)
		return ;
	dt = 1/dt;
	__m128	a = _mm_load_ps((float*)&aa);
	__m128	b = _mm_load_ps((float*)&bb);
	__m128	dt_x4 = _mm_load_ps1(&dt);
	__m128	step = _mm_mul_ps(_mm_sub_ps(b, a), dt_x4);
	float t = 0;
	while (t < 1)
	{
		alignas(16) float *f = (float *)&a;;
		int x = f[0];
		int y = f[1];
		float z = f[2];
		float altitude = f[3];
		int i = x + y * bmp.x_dim;
		if (z > ((t_zbuffer *)zbuffer)->z[i])
		{
			((t_zbuffer *)zbuffer)->z[i] = z;
			bmp.data[i] = bmp.color_table[(int)((COLOR_TABLE_SIZE-1) * altitude)];
			//bmp.data[i] = color_gradient(altitude, PURPLE, GRASS, PEACH);
		}
		a = _mm_add_ps(a, step);
		t += dt;
	}
}
