/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_movement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 15:28:03 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/27 17:14:01 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_cam_position(t_things *things)
{
	if (things->map != NULL)
	{
		things->cam->world.x = things->map->row_size / 2;
		things->cam->world.y = things->map->row_num / 2;
		things->cam->world.z = (things->map->z_min + things->map->z_max) / 2;
	}
	else
	{
		things->cam->world = ORIGIN;
	}
	things->cam->rot = ORIGIN;
}

void	translate_cam(t_cam *cam, int command)
{
	t_float3	lateral;
	float		step;

	step = 1.0;
	if (cam->projection == Oblique_Military)
		lateral = cam->up;
	else
	{
		lateral.x = -cam->dir.x;
		lateral.y = -cam->dir.y;
		lateral.z = 0.0;
		normalize(lateral);
	}
	if (command == GO_FWD)
		cam->world = add_float3(cam->world, scalar_mul(lateral, step));
	else if (command == GO_BACK)
		cam->world = add_float3(cam->world, scalar_mul(lateral, -step));
	else if (command == STRAFE_RIGHT)
		cam->world = add_float3(cam->world, scalar_mul(cam->right, step));
	else if (command == STRAFE_LEFT)
		cam->world = add_float3(cam->world, scalar_mul(cam->right, -step));
}
