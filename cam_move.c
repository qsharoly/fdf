/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 15:28:03 by qsharoly          #+#    #+#             */
/*   Updated: 2020/05/24 18:55:23 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_cam_position(t_things *things)
{
	if (things->map.rows != NULL)
	{
		things->cam.target.x = things->map.row_size / 2;
		things->cam.target.y = things->map.row_num / 2;
		things->cam.target.z = (things->map.z_min + things->map.z_max) / 2;
	}
	else
	{
		things->cam.target = ORIGIN;
	}
	things->cam.angle = ORIGIN;
}

void	translate_cam(t_cam *cam, int command)
{
	/*
	t_vec3	lateral;
	float	step;

	step = 1.0;
	if (cam->projection == Oblique_Military)
		lateral = cam->up;
	else
	{
		lateral.x = -cam->dir.x;
		lateral.y = -cam->dir.y;
		lateral.z = 0.0;
		normalize3(lateral);
	}
	if (command == GO_FWD)
		cam->target = add3(cam->target, scale(lateral, step));
	else if (command == GO_BACK)
		cam->target = add3(cam->target, scale(lateral, -step));
	else if (command == STRAFE_RIGHT)
		cam->target = add3(cam->target, scale(cam->right, step));
	else if (command == STRAFE_LEFT)
		cam->target = add3(cam->target, scale(cam->right, -step));
		*/
	if (command == GO_FWD)
		cam->target = add3(cam->target, rot_z(-cam->angle.z, YUNIT));
	else if (command == GO_BACK)
		cam->target = sub3(cam->target, rot_z(-cam->angle.z, YUNIT));
	else if (command == STRAFE_RIGHT)
		cam->target = add3(cam->target, rot_z(-cam->angle.z, XUNIT));
	else if (command == STRAFE_LEFT)
		cam->target = sub3(cam->target, rot_z(-cam->angle.z, XUNIT));
}
