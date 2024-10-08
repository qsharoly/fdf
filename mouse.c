/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 14:32:55 by qsharoly          #+#    #+#             */
/*   Updated: 2022/11/10 16:06:18 by kith             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mouse.h"
#include "keyboard.h"
#include "settings.h"

int	hook_mouse_move(int x, int y, t_things *th)
{
	int	dx;
	int	dy;

	dx = x - th->state.mousex;
	dy = y - th->state.mousey;
	if (th->state.lmb_is_down)
	{
		th->state.redraw = 1;
		if (th->state.shift_is_down)
		{
			th->cam.angle.z += M_PI / 128 * dx;
			th->cam.angle.x += M_PI / 128 * -dy;
		}
		else
		{
			float	factor = (float)th->map.rows / (XDIM * th->cam.zoom);
			cam_drag(&th->cam, dx * factor, dy * factor);
		}
	}
	th->state.mousex = x;
	th->state.mousey = y;
	return (0);
}

int	hook_mouse_press(int button, int x, int y, t_things *th)
{
	th->state.redraw = 1;
	if (button == MWHEELUP && th->state.ctrl_is_down)
		th->cam.altitude_scale *= 1.2;
	else if (button == MWHEELUP)
		th->cam.zoom *= 1.25;
	else if (button == MWHEELDOWN && th->state.ctrl_is_down)
		th->cam.altitude_scale *= 0.8;
	else if (button == MWHEELDOWN)
		th->cam.zoom *= 0.8;
	else if (button == LMB)
	{
		th->state.lmb_is_down = 1;
		th->state.mousex = x;
		th->state.mousey = y;
	}
	return (0);
}

int	hook_mouse_release(int button, int x, int y, t_things *th)
{
	(void)x;
	(void)y;
	if (button == LMB)
		th->state.lmb_is_down = 0;
	return (0);
}
