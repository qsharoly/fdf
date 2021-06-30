/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:29:02 by qsharoly          #+#    #+#             */
/*   Updated: 2021/06/30 21:15:23 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projection.h"
#include "libft.h"

t_vec4	vec4(float coordinates[4])
{
	t_vec4	new;

	new.v[X] = coordinates[X];
	new.v[Y] = coordinates[Y];
	new.v[Z] = coordinates[Z];
	new.v[W] = coordinates[W];
	return (new);
}

float	dot4(float a[4], float b[4])
{
	return (a[X] * b[X] + a[Y] * b[Y] + a[Z] * b[Z] + a[W] * b[W]);
}

static t_vec4	point4(float x, float y, float z)
{
	t_vec4	new;

	new.v[X] = x;
	new.v[Y] = y;
	new.v[Z] = z;
	new.v[W] = 1;
	return (new);
}

t_vec4	direction4(t_vec3 v)
{
	t_vec4	dir;

	dir.v[X] = v.x;
	dir.v[Y] = v.y;
	dir.v[Z] = v.z;
	dir.v[W] = 0;
	return (dir);
}

t_vec4	transform(t_mat4 m, t_vec4 v)
{
	t_vec4	res;

	res.v[X] = dot4(m.m[0], v.v);
	res.v[Y] = dot4(m.m[1], v.v);
	res.v[Z] = dot4(m.m[2], v.v);
	res.v[W] = dot4(m.m[3], v.v);
	return (res);
}

t_mat4	transpose(t_mat4 m)
{
	t_mat4	tr;
	int		i;
	int		j;

	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			tr.m[j][i] = m.m[i][j];
			i++;
		}
		j++;
	}
	return (tr);
}

t_mat4	compose(t_mat4 a, t_mat4 b)
{
	t_mat4	c;
	t_mat4	b_transposed;
	int		i;
	int		j;

	b_transposed = transpose(b);
	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			c.m[j][i] = dot4(a.m[j], b_transposed.m[i]);
			i++;
		}
		j++;
	}
	return (c);
}

t_mat4	zero_mat4(void)
{
	t_mat4	m;

	ft_bzero(&m.m[0][0], sizeof(m.m[0][0]) * 4);
	ft_bzero(&m.m[1][0], sizeof(m.m[0][0]) * 4);
	ft_bzero(&m.m[2][0], sizeof(m.m[0][0]) * 4);
	ft_bzero(&m.m[3][0], sizeof(m.m[0][0]) * 4);
	return (m);
}

t_mat4	identity_mat4(void)
{
	t_mat4	m;

	m = zero_mat4();
	m.m[0][0] = 1.0;
	m.m[1][1] = 1.0;
	m.m[2][2] = 1.0;
	m.m[3][3] = 1.0;
	return (m);
}

t_mat4	translation_mat4(float x, float y, float z)
{
	t_mat4	m;

	m = identity_mat4();
	m.m[0][3] = x;
	m.m[1][3] = y;
	m.m[2][3] = z;
	return (m);
}

t_mat4	scaling_mat4(float x_scale, float y_scale, float z_scale)
{
	t_mat4	m;

	m = zero_mat4();
	m.m[0][0] = x_scale;
	m.m[1][1] = y_scale;
	m.m[2][2] = z_scale;
	m.m[3][3] = 1;
	return (m);
}

t_mat4	rot_mat4_simple(char axis, float angle)
{
	t_mat4	m;

	m = identity_mat4();
	if (axis == X)
	{
		m.m[1][1] = cos(angle);
		m.m[1][2] = -sin(angle);
		m.m[2][1] = sin(angle);
		m.m[2][2] = cos(angle);
	}
	else if (axis == Y)
	{
		m.m[0][0] = cos(angle);
		m.m[0][2] = -sin(angle);
		m.m[2][0] = sin(angle);
		m.m[2][2] = cos(angle);
	}
	else if (axis == Z)
	{
		m.m[0][0] = cos(angle);
		m.m[0][1] = -sin(angle);
		m.m[1][0] = sin(angle);
		m.m[1][1] = cos(angle);
	}
	return (m);
}

t_mat4	rot_mat4(t_vec3 dir, float angle)
{
	t_mat4	m;
	float	sin_a;
	float	cos_a;

	dir = normalize3(dir);
	sin_a = sin(angle);
	cos_a = cos(angle);
	m = zero_mat4();
	m.m[0][0] = dir.x * dir.x + (dir.y * dir.y + dir.z * dir.z) * cos_a;
	m.m[0][1] = dir.x * dir.y * (1 - cos_a) - dir.z * sin_a;
	m.m[0][2] = dir.x * dir.z * (1 - cos_a) + dir.y * sin_a;
	m.m[1][0] = dir.x * dir.y * (1 - cos_a) + dir.z * sin_a;
	m.m[1][1] = dir.y * dir.y + (dir.x * dir.x + dir.z * dir.z) * cos_a;
	m.m[1][2] = dir.y * dir.z * (1 - cos_a) - dir.x * sin_a;
	m.m[2][0] = dir.x * dir.z * (1 - cos_a) - dir.y * sin_a;
	m.m[2][1] = dir.y * dir.z * (1 - cos_a) + dir.x * sin_a;
	m.m[2][2] = dir.z * dir.z + (dir.x * dir.x + dir.y * dir.y) * cos_a;
	m.m[3][3] = 1;
	return (m);
}

t_mat4	orthographic_mat4(t_cam *cam, t_bitmap bmp)
{
	t_mat4	m;
	float	top;
	float	right;
	float	f;
	float	n;

	m = zero_mat4();
	top = tan(0.5 * cam->fov) * cam->z_near;
	right = top * bmp.x_dim / bmp.y_dim;
	f = cam->z_far;
	n = cam->z_near;
	m.m[0][0] = n / top;
	m.m[1][1] = n / right;
	m.m[2][2] = -2 / (f - n);
	m.m[2][3] = -(f + n) / (f - n);
	m.m[3][3] = 1;
	return (m);
}

t_mat4	perspective_mat4(t_cam *cam, t_bitmap bmp)
{
	t_mat4	m;
	float	top;
	float	right;
	float	f;
	float	n;

	m = zero_mat4();
	top = tan(0.5 * cam->fov) * cam->z_near;
	right = top * bmp.x_dim / bmp.y_dim;
	f = cam->z_far;
	n = cam->z_near;
	m.m[0][0] = n / top;
	m.m[1][1] = n / right;
	m.m[2][2] = f / (f - n);
	m.m[2][3] = - f * n / (f - n);
	m.m[3][2] = 1;
	return (m);
}

void	calc_camera_transform(t_cam *cam, t_bitmap bmp)
{
	t_mat4	translation;
	t_mat4	rotation;
	t_mat4	distance;
	t_mat4	prj;
	t_mat4	scaling;

	translation = translation_mat4(-cam->target.x, -cam->target.y, -cam->target.z);
	translation = compose(scaling_mat4(1, 1, cam->altitude_scale), translation);
	rotation = compose(rot_mat4_simple(X, cam->angle.x), compose(rot_mat4_simple(Y, cam->angle.y), rot_mat4_simple(Z, cam->angle.z)));
	distance = translation_mat4(0, 0, cam->dist);
	if (cam->projection == Perspective)
	{
		scaling = scaling_mat4(cam->zoom * bmp.y_dim, cam->zoom * bmp.x_dim, -1);
		prj = perspective_mat4(cam, bmp);
	}
	else if (cam->projection == Axonometric)
	{
		scaling = scaling_mat4(cam->zoom * bmp.y_dim, cam->zoom * bmp.x_dim, 1);
		prj = orthographic_mat4(cam, bmp);
	}
	else
	{
		scaling = identity_mat4();
		prj = identity_mat4();
	}
	cam->transform = compose(prj, compose(distance, compose(scaling, compose(rotation, translation))));
}

t_vec3	persp_divide(t_vec4 v)
{
	float	invw;
	t_vec3	res;

	invw = 1 / v.v[W];
	res = (t_vec3){v.v[X] * invw, v.v[Y] * invw, v.v[Z] * invw};
	return (res);
}

t_vec3	geom_to_pixel(t_vec3 pt, const t_cam *cam)
{
	t_vec3	pixel;

	pixel = persp_divide(transform(cam->transform, point4(pt.x, pt.y, pt.z)));
	pixel.x = 0.5 * 640 + pixel.x;
	pixel.y = 0.5 * 480 + pixel.y;
	return (pixel);
}
