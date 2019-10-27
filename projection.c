/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_more.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:14:59 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/27 17:24:41 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "projection.h"

t_float3	project(t_float3 point, t_cam *cam, t_bitmap *bmp)
{
	t_float3	scr;
	float		ray_len;
	float		persp;

	point = add_float3(point, scalar_mul(cam->world, -1));
	point.z *= cam->altitude_mult;
	scr.z = (cam->dist - dot(point, cam->dir)) / dot(cam->dir, cam->proj_dir);
	if (cam->projection == Perspective)
		ray_len = scr.z;
	else
		ray_len = -dot(point, cam->dir) / dot(cam->dir, cam->proj_dir);
	point = add_float3(point, scalar_mul(cam->proj_dir, ray_len));
	scr.x = cam->zoom * dot(point, cam->right);
	scr.y = cam->zoom * dot(point, cam->up);
	if (cam->projection == Perspective)
	{
		persp = 0.5 * (cam->z_far - cam->z_near) / scr.z;
		scr.x *= persp;
		scr.y *= persp;
	}
	scr.x += 0.5 * bmp->x_dim;
	scr.y += 0.5 * bmp->y_dim;
	return (scr);
}

void		cam_setup_perspective(t_cam *cam)
{
	cam_setup_axonometric(cam);
	cam->z_near = 1;
	cam->z_far = 2 * cam->dist;
}

void		cam_setup_axonometric(t_cam *cam)
{
	cam->dir = ZUNIT;
	cam->dir = rot_x(M_PI / 3 + cam->rot.x, cam->dir);
	cam->dir = rot_z(M_PI * 3 / 4 + cam->rot.z, cam->dir);
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
