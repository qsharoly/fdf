/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 14:32:55 by qsharoly          #+#    #+#             */
/*   Updated: 2021/02/06 22:35:01 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mouse.h"

int		mouse_move(int x, int y, t_things *th)
{
	(void)x;
	(void)y;
	(void)th;
	return (0);
}

int		mouse_button(int button, int x, int y, t_things *th)
{
	(void)x;
	(void)y;
	th->state.redraw = 1;
	if (button == MWHEELUP)
		th->cam.zoom *= 1.25;
	else if (button == MWHEELDOWN)
		th->cam.zoom *= 0.8;
	return (0);
}
