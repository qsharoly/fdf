/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 15:28:03 by qsharoly          #+#    #+#             */
/*   Updated: 2022/05/14 11:54:31 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_cam(t_cam *cam, const t_map *map)
{
	if (map->vertices != NULL)
	{
		cam->target = (t_vec3){
			.x = map->per_row / 2,
			.y = map->rows / 2,
			.z = (map->z_min + map->z_max) / 2
		};
	}
	else
	{
		cam->target = ORIGIN;
	}
	cam->angle = ORIGIN;
	cam->zoom = 1;
}

void	cam_walk(t_cam *cam, int command)
{
	if (command == GO_FWD)
		cam->target = add3(cam->target, rot_z(-cam->angle.z, YUNIT));
	else if (command == GO_BACK)
		cam->target = sub3(cam->target, rot_z(-cam->angle.z, YUNIT));
	else if (command == STRAFE_RIGHT)
		cam->target = add3(cam->target, rot_z(-cam->angle.z, XUNIT));
	else if (command == STRAFE_LEFT)
		cam->target = sub3(cam->target, rot_z(-cam->angle.z, XUNIT));
}

//TODO: why must negate dx and dy?
void	cam_drag(t_cam *cam, float dx, float dy)
{
	t_vec3	delta;

	delta.x = -dx;
	delta.y = -dy;
	delta.z = 0;
	cam->target = add3(cam->target, rot_z(-cam->angle.z, delta));
}
