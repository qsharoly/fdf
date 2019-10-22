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

void	controls_who_need_redraw(int keycode, t_things *my)
{
	if (keycode == LETTER_S)
		toggle(&my->state->draw_stats);
	else if (keycode == LETTER_H)
		toggle(&my->state->draw_helpers);
	else if (keycode == LETTER_C)
		toggle(&my->state->draw_controls);
	else if (keycode == LETTER_P)
		my->state->projection = ++(my->state->projection) % N_PROJECTION_KINDS;
	else if (keycode == LETTER_J)
		my->cam->zoom *= 1.2;
	else if (keycode == LETTER_K)
		my->cam->zoom *= 0.8;
	else if (keycode == LETTER_U)
		my->cam->altitude_mult *= 1.2;
	else if (keycode == LETTER_I)
		my->cam->altitude_mult *= 0.8;
	else if (keycode == LETTER_B)
		toggle(&my->state->use_z_buf);
}

int		key_controls(int keycode, t_things *my)
{
	my->state->redraw = 0;
	if (my->state->print_keycodes)
		ft_putnbr_endl(keycode);
	if (keycode == LETTER_Q || keycode == ESC)
		free_things_and_exit(my);
	else if (keycode == SPACEBAR)
		toggle(&my->state->animation_pause);
	else if (keycode == LETTER_N && my->state->animation_pause)
		my->state->animation_step = 1;
	else if (keycode == LETTER_D)
		toggle(&my->state->print_stats);
	else if (keycode == LETTER_A)
		toggle(&my->state->print_keycodes);
	else
	{
		my->state->redraw = 1;
		controls_who_need_redraw(keycode, my);
	}
	return (0);
}
