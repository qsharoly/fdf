/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:46:55 by qsharoly          #+#    #+#             */
/*   Updated: 2021/07/04 01:55:44 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"
#include "fdf.h"

int	key_release(int keycode, t_things *th)
{
	if (keycode == L_SHIFT || keycode == R_SHIFT)
	{
		th->state.dragging &= ~SHIFT_MASK;
	}
	return (0);
}

void	camera_movements(int keycode, t_things *th)
{
	if (keycode == K_CAM_RESET)
		reset_cam(th);
	else if (keycode == K_CAM_TURN_LEFT)
		th->cam.angle.z += M_PI / 64;
	else if (keycode == K_CAM_TURN_RIGHT)
		th->cam.angle.z -= M_PI / 64;
	else if (keycode == K_CAM_NOSE_DOWN)
		th->cam.angle.x += M_PI / 64;
	else if (keycode == K_CAM_NOSE_UP)
		th->cam.angle.x -= M_PI / 64;
	else if (keycode == K_CAM_GO_FWD)
		cam_walk(&th->cam, GO_FWD);
	else if (keycode == K_CAM_GO_BACK)
		cam_walk(&th->cam, GO_BACK);
	else if (keycode == K_CAM_STRAFE_LEFT)
		cam_walk(&th->cam, STRAFE_LEFT);
	else if (keycode == K_CAM_STRAFE_RIGHT)
		cam_walk(&th->cam, STRAFE_RIGHT);
}

void	controls_who_need_redraw(int keycode, t_things *th)
{
	if (keycode == K_DRAW_STATS)
		TOGGLE(th->state.draw_stats);
	else if (keycode == K_DRAW_AXIS)
		TOGGLE(th->state.draw_helpers);
	else if (keycode == K_DRAW_CONTROLS)
		TOGGLE(th->state.draw_controls);
	else if (keycode == K_NEXT_PROJECTION)
		th->cam.projection = (th->cam.projection + 1) % N_PROJECTION_KINDS;
	else if (keycode == K_ZOOM_IN)
		th->cam.zoom *= 1.2;
	else if (keycode == K_ZOOM_OUT)
		th->cam.zoom *= 0.8;
	else if (keycode == K_ALTITUDE_SCALE_UP)
		th->cam.altitude_scale *= 1.2;
	else if (keycode == K_ALTITUDE_SCALE_DOWN)
		th->cam.altitude_scale *= 0.8;
	else if (keycode == K_TOGGLE_ZBUF)
		TOGGLE(th->state.use_zbuf);
	else
		camera_movements(keycode, th);
}

int		key_press(int keycode, t_things *th)
{
	th->state.redraw = 0;
	if (th->state.print_keycodes)
		ft_putnbr_endl(keycode);
	if (keycode == L_SHIFT || keycode == R_SHIFT)
		th->state.dragging |= SHIFT_MASK;
	else if (keycode == K_EXIT1 || keycode == K_EXIT2)
		free_things_and_exit(th);
	else if (keycode == K_ANIM_PAUSE)
		TOGGLE(th->state.animation_running);
	else if (keycode == K_ANIM_STEP)
		th->state.animation_step = 1;
	else if (keycode == K_PRINT_KEYCODES)
		TOGGLE(th->state.print_keycodes);
	else
	{
		th->state.redraw = 1;
		controls_who_need_redraw(keycode, th);
	}
	return (0);
}
