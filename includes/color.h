/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:41:56 by qsharoly          #+#    #+#             */
/*   Updated: 2022/11/07 07:52:44 by kith             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define BLACK		0x00000000 //rgba_to_int((t_rgba) {0, 0, 0, 0})
# define WHITE		0x00ffffff //rgba_to_int((t_rgba) {255, 255, 255, 0})
# define RED		0x00ff0000 //rgba_to_int((t_rgba) {255, 0, 0, 0})
# define GREEN		0x0000ff00 //rgba_to_int((t_rgba) {0, 255, 0, 0})
# define BLUE		0x000000ff //rgba_to_int((t_rgba) {0, 0, 255, 0})
# define PURPLE		0x00961efa //rgba_to_int((t_rgba) {150, 30, 250, 0})
# define LIGHTGREEN	0x001efa96 //rgba_to_int((t_rgba) {30, 250, 150, 0})
# define PEACH		0x00fa961e //rgba_to_int((t_rgba) {250, 150, 30, 0})
# define GRASS		0x001e9650 //rgba_to_int((t_rgba) {30, 150, 80, 0})

# define COLOR_TABLE_SIZE 1000

typedef struct	s_argb
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_argb;

int		mix(int col1, int col2, float ratio);
t_argb	int_to_argb(int color);
int		argb_to_int(t_argb color);
int		color_gradient(float t, int bottom_color, int middle_color, int top_color);
void	init_color_table(int table[COLOR_TABLE_SIZE]);

#endif
