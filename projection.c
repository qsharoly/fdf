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

t_float3	project(t_float3 point, t_cam *cam, t_bitmap *bmp)
{
	t_float3	screen;
	float		ray_len;
	float		persp;

	point.z *= cam->altitude_mult;
	point = add_float3(point, scalar_mul(cam->world, -1));
	screen.z = (cam->dist - dot(point, cam->dir)) / dot(cam->dir, cam->proj_dir);
	if (cam->projection == Perspective)
		ray_len = screen.z;
	else
		ray_len = -dot(point, cam->dir) / dot(cam->dir, cam->proj_dir);
	point = add_float3(point, scalar_mul(cam->proj_dir, ray_len));
	screen.x = cam->zoom * dot(point, cam->right);
	screen.y = cam->zoom * dot(point, cam->up);
	if (cam->projection == Perspective)
	{
		persp = 0.5 * (cam->z_far - cam->z_near) / screen.z;
		screen.x *= persp;
		screen.y *= persp;
	}
	screen.x += 0.5 * bmp->x_dim;
	screen.y += 0.5 * bmp->y_dim;
	return (screen);
}
#include "libft.h"
void		translate_cam(t_cam *cam, int command)
{
	t_float3	lateral;
	float		step;

	step = 1.0;
	lateral.x = -cam->dir.x;
	lateral.y = -cam->dir.y;
	lateral.z = 0.0;
	normalize(lateral);
	if (command == GO_FWD)
		cam->world = add_float3(cam->world, scalar_mul(lateral, step));
	else if (command == GO_BACK)
		cam->world = add_float3(cam->world, scalar_mul(lateral, -step));
	else if (command == STRAFE_RIGHT)
		cam->world = add_float3(cam->world, scalar_mul(cam->right, step));
	else if (command == STRAFE_LEFT)
		cam->world = add_float3(cam->world, scalar_mul(cam->right, -step));
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
