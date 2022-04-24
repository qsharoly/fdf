/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:10:00 by qsharoly          #+#    #+#             */
/*   Updated: 2022/04/24 13:56:08 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H

typedef unsigned int	t_uint;
/*
typedef struct			s_uint2
{
	t_uint	x;
	t_uint	y;
}						t_uint2;
typedef struct			s_rect
{
	t_uint	x;
	t_uint	y;
	t_uint	width;
	t_uint	height;
}						t_rect;
*/
typedef struct			s_bitmap
{
	t_uint			*data;
	t_uint			x_dim;
	t_uint			y_dim;
	int				*color_table;
}						t_bitmap;

int						get_pixel(t_bitmap bmp, t_uint x, t_uint y);
void					set_pixel(t_bitmap bmp, t_uint x, t_uint y, int color);
/*
t_rect					rect(t_uint x, t_uint y, t_uint width, t_uint height);
void					fill_rect(t_bitmap bmp, t_rect rect, int color);
*/

#endif
