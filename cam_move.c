/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 15:28:03 by qsharoly          #+#    #+#             */
/*   Updated: 2021/02/06 23:18:11 by debby            ###   ########.fr       */
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
