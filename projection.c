/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_more.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:14:59 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/24 19:44:05 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "projection.h"

void		reset_z_buf(t_cam *cam)
{
	t_uint		i;

	i = 0;
	while (i < cam->z_buf_size)
	{
		cam->z_buf[i] = -INFINITY;
		i++;
	}
}

t_float3	project(t_float3 point, t_cam *cam, t_bitmap *bmp)
{
	t_float3	proj;
	t_float3	screen;
	float		coeff;

	point = add_float3(point, scalar_mul(cam->world, -1));
	point.z *= cam->altitude_mult;
	coeff = (cam->dist - dot(point, cam->dir)) / dot(cam->dir, cam->proj_dir);
	proj = add_float3(point, scalar_mul(cam->proj_dir, coeff));
	screen.z = dot(point, cam->dir);
	screen.x = cam->zoom * dot(proj, cam->right) + 0.5 * bmp->x_dim;
	screen.y = cam->zoom * dot(proj, cam->up) + 0.5 * bmp->y_dim;
	return (screen);
}

void		cam_setup_axonometric(t_cam *cam, float cam_rotation)
{
	cam->dir.x = sin(M_PI * 0.25 + cam_rotation);
	cam->dir.y = cos(M_PI * 0.25 + cam_rotation);
	cam->dir.z = cos(M_PI / 3);
	cam->dir = normalize(cam->dir);
	cam->right.x = cam->dir.y;
	cam->right.y = -cam->dir.x;
	cam->right.z = 0;
	cam->right = normalize(cam->right);
	cam->up = cross(cam->dir, cam->right);
	cam->proj_dir = cam->dir;
}

void		cam_setup_military(t_cam *cam)
{
	cam->right = add_float3(XUNIT, scalar_mul(YUNIT, -1));
	cam->right = normalize(cam->right);
	cam->dir = ZUNIT;
	cam->up = cross(cam->dir, cam->right);
	cam->proj_dir.x = 1 * sin(M_PI * 0.25);
	cam->proj_dir.y = 1 * cos(M_PI * 0.25);
	cam->proj_dir.z = 1;
	cam->proj_dir = normalize(cam->proj_dir);
}

void		cam_setup_cavalier(t_cam *cam)
{
	cam->right = XUNIT;
	cam->dir = YUNIT;
	cam->up = scalar_mul(ZUNIT, -1);
	cam->proj_dir = rot_z(-0.15 * M_PI, cam->dir);
	cam->proj_dir = rot_x(0.15 * M_PI, cam->proj_dir);
}
