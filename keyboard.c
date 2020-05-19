/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:46:55 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/27 16:32:50 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"
#include "fdf.h"

void	toggle(int *var)
{
	*var = !*var;
}

void	camera_movements(int keycode, t_things *my)
{
	if (keycode == K_CAM_RESET)
		reset_cam_position(my);
	else if (keycode == K_CAM_TURN_LEFT)
		my->cam->rot.z += M_PI / 64;
	else if (keycode == K_CAM_TURN_RIGHT)
		my->cam->rot.z -= M_PI / 64;
	else if (keycode == K_CAM_NOSE_DOWN)
		my->cam->rot.x += M_PI / 64;
	else if (keycode == K_CAM_NOSE_UP)
		my->cam->rot.x -= M_PI / 64;
	else if (keycode == K_CAM_GO_FWD)
		translate_cam(my->cam, GO_FWD);
	else if (keycode == K_CAM_GO_BACK)
		translate_cam(my->cam, GO_BACK);
	else if (keycode == K_CAM_STRAFE_LEFT)
		translate_cam(my->cam, STRAFE_LEFT);
	else if (keycode == K_CAM_STRAFE_RIGHT)
		translate_cam(my->cam, STRAFE_RIGHT);
}

void	controls_who_need_redraw(int keycode, t_things *my)
{
	if (keycode == K_DRAW_STATS)
		toggle(&my->state->draw_stats);
	else if (keycode == K_DRAW_AXIS)
		toggle(&my->state->draw_helpers);
	else if (keycode == K_DRAW_CONTROLS)
		toggle(&my->state->draw_controls);
	else if (keycode == K_NEXT_PROJECTION)
		my->cam->projection = (my->cam->projection + 1) % N_PROJECTION_KINDS;
	else if (keycode == K_ZOOM_IN)
		my->cam->zoom *= 1.2;
	else if (keycode == K_ZOOM_OUT)
		my->cam->zoom *= 0.8;
	else if (keycode == K_ALTITUDE_SCALE_UP)
		my->cam->altitude_mult *= 1.2;
	else if (keycode == K_ALTITUDE_SCALE_DOWN)
		my->cam->altitude_mult *= 0.8;
	else if (keycode == K_TOGGLE_ZBUF)
		toggle(&my->state->use_z_buf);
	else
		camera_movements(keycode, my);
}

int		key_controls(int keycode, t_things *my)
{
	my->state->redraw = 0;
	if (my->state->print_keycodes)
		ft_putnbr_endl(keycode);
	if (keycode == K_EXIT1 || keycode == K_EXIT2)
		free_things_and_exit(my);
	else if (keycode == K_ANIM_PAUSE)
		toggle(&my->state->animation_pause);
	else if (keycode == K_ANIM_STEP && my->state->animation_pause)
		my->state->animation_step = 1;
	else if (keycode == K_PRINT_KEYCODES)
		toggle(&my->state->print_keycodes);
	else
	{
		my->state->redraw = 1;
		controls_who_need_redraw(keycode, my);
	}
	return (0);
}
