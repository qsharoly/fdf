/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:40:11 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/12 16:40:42 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_H
# define KEYBOARD_H

# define SPACEBAR 49
# define LETTER_Q 12
# define LETTER_N 45
# define LETTER_S 1
# define LETTER_D 2
# define LETTER_H 4
# define LETTER_C 8
# define LETTER_U 32
# define LETTER_I 34
# define LETTER_J 38
# define LETTER_K 40
# define LETTER_P 35
# define L_SHIFT 257
# define R_SHIFT 258
# define ESC 53

void	toggle(int *var);
int		key_controls(int keycode, void *param);

#endif
