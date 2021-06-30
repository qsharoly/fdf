/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 14:32:55 by qsharoly          #+#    #+#             */
/*   Updated: 2021/06/30 13:41:03 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mouse.h"

int		mouse_move(int x, int y, t_things *th)
{
	if (th->state.dragging & LMB_MASK)
	{
		th->state.redraw = 1;
		th->cam.angle.z += M_PI / 64 * (x - th->state.mousex);
		th->cam.angle.x += M_PI / 64 * (y - th->state.mousey);
	}
	th->state.mousex = x;
	th->state.mousey = y;
	return (0);
}

int		mouse_press(int button, int x, int y, t_things *th)
{
	th->state.redraw = 1;
	if (button == MWHEELUP)
		th->cam.zoom *= 1.25;
	else if (button == MWHEELDOWN)
		th->cam.zoom *= 0.8;
	else if (button == LMB)
	{
		th->state.dragging |= LMB_MASK;
		th->state.mousex = x;
		th->state.mousey = y;
	}
	return (0);
}

int		mouse_release(int button, int x, int y, t_things *th)
{
	(void)x;
	(void)y;
	if (button == LMB)
		th->state.dragging &= ~LMB_MASK;
	return (0);
}
