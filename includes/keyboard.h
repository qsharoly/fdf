/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:40:11 by qsharoly          #+#    #+#             */
/*   Updated: 2021/07/02 03:47:17 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_H
# define KEYBOARD_H

# if __APPLE__
#  define ESC 53
#  define SPACEBAR 49
#  define COMMA 43
#  define PERIOD 47
#  define LETTER_A 0
#  define LETTER_B 11
#  define LETTER_C 8
#  define LETTER_D 2
#  define LETTER_E 14
#  define LETTER_F 3
#  define LETTER_G 5
#  define LETTER_H 4
#  define LETTER_I 34
#  define LETTER_J 38
#  define LETTER_K 40
#  define LETTER_L 37
#  define LETTER_N 45
#  define LETTER_M 46
#  define LETTER_O 31
#  define LETTER_P 35
#  define LETTER_Q 12
#  define LETTER_R 15
#  define LETTER_S 1
#  define LETTER_T 17
#  define LETTER_U 32
#  define LETTER_V 9
#  define LETTER_W 13
#  define LETTER_X 7
#  define LETTER_Y 16
#  define LETTER_Z 6
#  define L_SHIFT 257
#  define R_SHIFT 258
# endif

# if __linux__
#  define ESC 65307
#  define SPACEBAR 32
#  define COMMA 44
#  define MINUS 45
#  define PERIOD 46
#  define EQUALS 61
#  define LETTER_A 97
#  define LETTER_B 98
#  define LETTER_C 99
#  define LETTER_D 100
#  define LETTER_E 101
#  define LETTER_F 102
#  define LETTER_G 103
#  define LETTER_H 104
#  define LETTER_I 105
#  define LETTER_J 106
#  define LETTER_K 107
#  define LETTER_L 108
#  define LETTER_M 109
#  define LETTER_N 110
#  define LETTER_O 111
#  define LETTER_P 112
#  define LETTER_Q 113
#  define LETTER_R 114
#  define LETTER_S 115
#  define LETTER_T 116
#  define LETTER_U 117
#  define LETTER_V 118
#  define LETTER_W 119
#  define LETTER_X 120
#  define LETTER_Y 121
#  define LETTER_Z 122
# endif

# define K_EXIT1 ESC
# define K_EXIT2 LETTER_Q
# define K_PRINT_KEYCODES LETTER_A
# define K_ANIM_PAUSE SPACEBAR
# define K_ANIM_STEP LETTER_N
# define K_ZOOM_IN COMMA
# define K_ZOOM_OUT PERIOD
# define K_ALTITUDE_SCALE_UP LETTER_T
# define K_ALTITUDE_SCALE_DOWN LETTER_G
# define K_TOGGLE_ZBUF LETTER_B
# define K_NEXT_PROJECTION LETTER_P
# define K_DRAW_CONTROLS LETTER_C
# define K_DRAW_AXIS LETTER_X
# define K_DRAW_STATS LETTER_Z
# define K_CAM_RESET LETTER_R
# define K_CAM_NOSE_UP LETTER_H
# define K_CAM_NOSE_DOWN LETTER_Y
# define K_CAM_TURN_LEFT LETTER_U
# define K_CAM_TURN_RIGHT LETTER_O
# define K_CAM_GO_FWD LETTER_I
# define K_CAM_GO_BACK LETTER_K
# define K_CAM_STRAFE_LEFT LETTER_J
# define K_CAM_STRAFE_RIGHT LETTER_L

#endif
