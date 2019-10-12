/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_more.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:14:59 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/12 16:53:19 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "projection.h"

t_float3	normalize(t_float3 vec)
{
	return (scalar_mul(vec, 1 / length3(vec)));
}

t_float3	project(t_float3 point, t_cam cam, t_bitmap *bmp)
{
	t_float3	proj;
	t_float3	screen;
	float		coeff;

	point = add_float3(point, scalar_mul(cam.world, -1));
	point.z *= cam.altitude_mult;
	coeff = (cam.dist - dot(point, cam.dir)) / dot(cam.dir, cam.proj_dir);
	proj = add_float3(point, scalar_mul(cam.proj_dir, coeff));
	screen.x = cam.fov * dot(proj, cam.right) + 0.5 * bmp->x_dim;
	screen.y = cam.fov * dot(proj, cam.up) + 0.5 * bmp->y_dim;
	screen.z = dot(proj, cam.dir);
	return (screen);
}
