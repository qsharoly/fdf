/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:29:02 by qsharoly          #+#    #+#             */
/*   Updated: 2022/04/12 14:08:01 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "settings.h"
#include "libft.h"

float	dot4(const t_vec4 a, const t_vec4 b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3]);
}

void	point4(t_vec4 tgt, const t_vec3 src)
{
	tgt[X] = src.x;
	tgt[Y] = src.y;
	tgt[Z] = src.z;
	tgt[W] = 1;
}

void	direction4(t_vec4 tgt, const t_vec3 src)
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
	v[X] = t[X];
	v[Y] = t[Y];
	v[Z] = t[Z];
	v[W] = t[W];
}

void	compose(t_mat4 b, const t_mat4 a)
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
	ft_memcpy(b, prod, 16*sizeof(float));
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
	float	cos_a;
	float	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	identity_mat4(m);
	if (axis == X)
	{
		m[1][1] = cos_a;
		m[1][2] = -sin_a;
		m[2][1] = sin_a;
		m[2][2] = cos_a;
	}
	else if (axis == Y)
	{
		m[0][0] = cos_a;
		m[0][2] = -sin_a;
		m[2][0] = sin_a;
		m[2][2] = cos_a;
	}
	else if (axis == Z)
	{
		m[0][0] = cos_a;
		m[0][1] = -sin_a;
		m[1][0] = sin_a;
		m[1][1] = cos_a;
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

void	orthographic_mat4(t_mat4 m, t_cam *cam)
{
	float	top;
	float	right;
	float	f;
	float	n;

	top = tan(0.5 * cam->fov) * cam->dist;
	right = top * cam->aspect;
	f = cam->z_far;
	n = cam->z_near;
	zero_mat4(m);
	m[0][0] = 1 / top;
	m[1][1] = 1 / right;
	m[2][2] = 2 / (f - n);
	m[2][3] = -(f + n) / (f - n);
	m[3][3] = 1;
}

void	perspective_mat4(t_mat4 m, t_cam *cam)
{
	float	top;
	float	right;
	float	n; //near: from eye to screen
	float	f; //far: from eye to clipping plane

	top = tan(0.5 * cam->fov) * cam->z_near;
	right = top * cam->aspect;
	n = cam->z_near;
	f = cam->z_far;
	zero_mat4(m);
	m[0][0] = n / top;
	m[1][1] = n / right;
	m[2][2] = f / (f - n);
	m[2][3] = f * n / (f - n);
	m[3][2] = -1;
}

void	calc_camera_transform(t_cam *cam)
{
	static t_mat4	t;
	static t_mat4	zstretch;
	static t_mat4	rx;
	static t_mat4	ry;
	static t_mat4	rz;
	static t_mat4	dist;
	static t_mat4	proj;
	static t_mat4	zoom;

	translation_mat4(t, -cam->target.x, -cam->target.y, -cam->target.z);
	scaling_mat4(zstretch, 1, 1, cam->altitude_scale);
	rot_mat4_simple(rx, X, cam->angle.x);
	rot_mat4_simple(ry, Y, cam->angle.y);
	rot_mat4_simple(rz, Z, cam->angle.z);
	translation_mat4(dist, 0, 0, -(cam->z_near + cam->dist));
	if (cam->projection == Perspective)
		perspective_mat4(proj, cam);
	else
		orthographic_mat4(proj, cam);
	scaling_mat4(zoom, cam->zoom, cam->zoom, cam->zoom);
	identity_mat4(cam->matrix);
	compose(cam->matrix, t);
	compose(cam->matrix, zstretch);
	compose(cam->matrix, rz);
	compose(cam->matrix, rx);
	compose(cam->matrix, dist);
	compose(cam->matrix, proj);
	compose(cam->matrix, zoom);
}

static void	persp_divide(t_vec4 v)
{
	v[X] /= v[W];
	v[Y] /= v[W];
	v[Z] /= v[W];
	v[W] = 1;
}

t_vec3	geom_to_pixel(t_vec3 point, const t_cam *cam)
{
	t_vec3	pixel;
	t_vec4	p4;

	point4(p4, point);
	transform(cam->matrix, p4);
	persp_divide(p4);
	pixel.x = (p4[X] + 1) * XDIM / 2;
	pixel.y = (p4[Y] + 1) * YDIM / 2;
	pixel.z = p4[Z];
	return (pixel);
}
