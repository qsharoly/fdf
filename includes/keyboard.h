/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:40:11 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/15 17:15:56 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_H
# define KEYBOARD_H

# define X11_KEYCODES

# ifdef MACOS_KEYCODES
#  define ESC 53
#  define SPACEBAR 49
#  define LETTER_Q 12
#  define LETTER_N 45
#  define LETTER_A 0
#  define LETTER_S 1
#  define LETTER_D 2
#  define LETTER_H 4
#  define LETTER_C 8
#  define LETTER_B 11
#  define LETTER_U 32
#  define LETTER_I 34
#  define LETTER_J 38
#  define LETTER_K 40
#  define LETTER_P 35
#  define L_SHIFT 257
#  define R_SHIFT 258
# endif

# ifdef X11_KEYCODES
#  define ESC 65307
#  define SPACEBAR 32
#  define LETTER_Q 113
#  define LETTER_P 112
#  define LETTER_J 106
#  define LETTER_K 107
#  define LETTER_U 117
#  define LETTER_I 105
#  define LETTER_N 110
#  define LETTER_A 97
#  define LETTER_B 98
#  define LETTER_C 99
#  define LETTER_D 100
#  define LETTER_S 115
#  define LETTER_H 104
# endif

void	toggle(int *var);
int		key_controls(int keycode, void *param);

#endif
