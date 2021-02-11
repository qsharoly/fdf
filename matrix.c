/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:29:02 by qsharoly          #+#    #+#             */
/*   Updated: 2021/02/11 15:59:07 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projection.h"
#include "libft.h"

float	dot4(const t_vec4 a, const t_vec4 b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3]);
}

void	point4(t_vec4 tgt, t_vec3 src)
{
	tgt[X] = src.x;
	tgt[Y] = src.y;
	tgt[Z] = src.z;
	tgt[W] = 1;
}

void	direction4(t_vec4 tgt, t_vec3 src)
{
	tgt[X] = src.x;
	tgt[Y] = src.y;
	tgt[Z] = src.z;
	tgt[W] = 0;
}

void	transform(const t_mat4 m, t_vec4 v)
{
	t_vec4 t;
	t[X] = dot4(m[0], v);
	t[Y] = dot4(m[1], v);
	t[Z] = dot4(m[2], v);
	t[W] = dot4(m[3], v);
	ft_memcpy(v, t, 4 * sizeof(*v));
}

void	mmul(t_mat4 a, const t_mat4 b)
{
	int		i;
	int		j;
	t_mat4	prod;

	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			prod[j][i] = a[j][0]*b[0][i] + a[j][1]*b[1][i]
						+ a[j][2]*b[2][i] + a[j][3]*b[3][i];
			i++;
		}
		j++;
	}
	ft_memcpy(a, prod, 16*sizeof(float));
}

void	zero_mat4(t_mat4 m)
{
	ft_bzero(m, sizeof(**m) * 16);
}

void	identity_mat4(t_mat4 m)
{
	zero_mat4(m);
	m[0][0] = 1.0;
	m[1][1] = 1.0;
	m[2][2] = 1.0;
	m[3][3] = 1.0;
}

void	translation_mat4(t_mat4 m, float x, float y, float z)
{
	identity_mat4(m);
	m[0][3] = x;
	m[1][3] = y;
	m[2][3] = z;
}

void	scaling_mat4(t_mat4 m, float x_scale, float y_scale, float z_scale)
{
	zero_mat4(m);
	m[0][0] = x_scale;
	m[1][1] = y_scale;
	m[2][2] = z_scale;
	m[3][3] = 1;
}

void	rot_mat4_simple(t_mat4 m, char axis, float angle)
{
	identity_mat4(m);
	if (axis == X)
	{
		m[1][1] = cos(angle);
		m[1][2] = -sin(angle);
		m[2][1] = sin(angle);
		m[2][2] = cos(angle);
	}
	else if (axis == Y)
	{
		m[0][0] = cos(angle);
		m[0][2] = -sin(angle);
		m[2][0] = sin(angle);
		m[2][2] = cos(angle);
	}
	else if (axis == Z)
	{
		m[0][0] = cos(angle);
		m[0][1] = -sin(angle);
		m[1][0] = sin(angle);
		m[1][1] = cos(angle);
	}
}

void	rot_mat4(t_mat4 m, t_vec3 dir, float angle)
{
	float	sin_a;
	float	cos_a;

	sin_a = sin(angle);
	cos_a = cos(angle);
	dir = normalize3(dir);
	zero_mat4(m);
	m[0][0] = dir.x * dir.x + (dir.y * dir.y + dir.z * dir.z) * cos_a;
	m[0][1] = dir.x * dir.y * (1 - cos_a) - dir.z * sin_a;
	m[0][2] = dir.x * dir.z * (1 - cos_a) + dir.y * sin_a;
	m[1][0] = dir.x * dir.y * (1 - cos_a) + dir.z * sin_a;
	m[1][1] = dir.y * dir.y + (dir.x * dir.x + dir.z * dir.z) * cos_a;
	m[1][2] = dir.y * dir.z * (1 - cos_a) - dir.x * sin_a;
	m[2][0] = dir.x * dir.z * (1 - cos_a) - dir.y * sin_a;
	m[2][1] = dir.y * dir.z * (1 - cos_a) + dir.x * sin_a;
	m[2][2] = dir.z * dir.z + (dir.x * dir.x + dir.y * dir.y) * cos_a;
	m[3][3] = 1;
}

void	orthographic_mat4(t_mat4 m, t_cam *cam, t_bitmap bmp)
{
	float	top;
	float	right;
	float	f;
	float	n;

	zero_mat4(m);
	top = tan(0.5 * cam->fov) * cam->z_near;
	right = top * bmp.x_dim / bmp.y_dim;
	f = cam->z_far;
	n = cam->z_near;
	m[0][0] = n / top;
	m[1][1] = n / right;
	m[2][2] = -2 / (f - n);
	m[2][3] = -(f + n) / (f - n);
	m[3][3] = 1;
}

void	perspective_mat4(t_mat4 m, t_cam *cam, t_bitmap bmp)
{
	float	top;
	float	right;
	float	f;
	float	n;

	zero_mat4(m);
	top = tan(0.5 * cam->fov) * cam->z_near;
	right = top * bmp.x_dim / bmp.y_dim;
	f = cam->z_far;
	n = cam->z_near;
	m[0][0] = n / top;
	m[1][1] = n / right;
	m[2][2] = f / (f - n);
	m[2][3] = - f * n / (f - n);
	m[3][2] = 1;
}

void	calc_camera_matrix(t_cam *cam, t_bitmap bmp)
{
	t_mat4	t;
	t_mat4	rx;
	t_mat4	ry;
	t_mat4	rz;
	t_mat4	s;
	t_mat4	dist;
	t_mat4	p;

	translation_mat4(t, -cam->target.x, -cam->target.y, -cam->target.z);
	rot_mat4_simple(rx, X, cam->angle.x);
	rot_mat4_simple(ry, Y, cam->angle.y);
	rot_mat4_simple(rz, Z, cam->angle.z);
	scaling_mat4(s, 1, 1, cam->altitude_scale);
	identity_mat4(cam->matrix);
	mmul(cam->matrix, s);
	mmul(cam->matrix, rz);
	mmul(cam->matrix, ry);
	mmul(cam->matrix, rx);
	mmul(cam->matrix, t);
	translation_mat4(dist, 0, 0, cam->dist);
	if (cam->projection == Perspective)
	{
		scaling_mat4(s, cam->zoom * bmp.y_dim, cam->zoom * bmp.x_dim, 1);
		perspective_mat4(p, cam, bmp);
	}
	else if (cam->projection == Axonometric)
	{
		scaling_mat4(s, cam->zoom * bmp.y_dim, cam->zoom * bmp.x_dim, 1);
		orthographic_mat4(p, cam, bmp);
	}
	else
	{
		identity_mat4(s);
		identity_mat4(p);
	}
	mmul(cam->matrix, dist);
	mmul(cam->matrix, s);
	mmul(cam->matrix, p);
}

t_vec3	persp_divide(t_vec4 v)
{
	t_vec3	res;

	res.x = v[X] / v[W];
	res.y = v[Y] / v[W];
	res.z = v[Z] / v[W];
	return (res);
}

t_vec3	geom_to_pixel(t_vec3 point, const t_cam *cam)
{
	t_vec3	pixel;
	t_vec4	p4;

	point4(p4, point);
	transform(cam->matrix, p4);
	pixel = persp_divide(p4);
	pixel.x = 0.5 * 640 + pixel.x;
	pixel.y = 0.5 * 480 + pixel.y;
	return (pixel);
}
