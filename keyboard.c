/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:46:55 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/15 16:34:19 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"
#include "fdf.h"

void	toggle(int *var)
{
	*var = (*var + 1) % 2;
}

int		controls_who_need_redraw(int keycode, void *param)
{
	t_my_state	*st;

	st = ((t_things *)param)->state;
	if (keycode == LETTER_S)
		toggle(&st->draw_stats);
	else if (keycode == LETTER_H)
		toggle(&st->draw_helpers);
	else if (keycode == LETTER_C)
		toggle(&st->draw_controls);
	else if (keycode == LETTER_P)
		st->projection = ++(st->projection) % N_PROJECTION_KINDS;
	else if (keycode == LETTER_J)
		((t_things *)param)->cam->fov *= 1.2;
	else if (keycode == LETTER_K)
		((t_things *)param)->cam->fov *= 0.8;
	else if (keycode == LETTER_U)
		((t_things *)param)->cam->altitude_mult *= 1.2;
	else if (keycode == LETTER_I)
		((t_things *)param)->cam->altitude_mult *= 0.8;
	else if (keycode == LETTER_B)
		toggle(&st->use_z_buf);
	return (0);
}

int		key_controls(int keycode, void *param)
{
	t_my_state	*st;
	int			ret;

	ret = 0;
	st = ((t_things *)param)->state;
	if (st->print_keycodes)
		ft_putnbr_endl(keycode);
	st->redraw = 0;
	if (keycode == LETTER_Q || keycode == ESC)
		st->stop_program = 1;
	else if (keycode == SPACEBAR)
		toggle(&st->frame_advance);
	else if ((keycode == LETTER_N) && (st->frame_advance == 1))
		st->do_step = 1;
	else if (keycode == LETTER_D)
		toggle(&st->print_stats);
	else if (keycode == LETTER_A)
		toggle(&st->print_keycodes);
	else
	{
		st->redraw = 1;
		ret = controls_who_need_redraw(keycode, param);
	}
	return (ret);
}
