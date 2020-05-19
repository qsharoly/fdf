/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:10:00 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/06 16:42:49 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H

typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;
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
typedef struct			s_rgba
{
	t_uchar	r;
	t_uchar	g;
	t_uchar	b;
	t_uchar	a;
}						t_rgba;
typedef struct			s_bitmap
{
	t_uint			*data;
	t_uint			x_dim;
	t_uint			y_dim;
}						t_bitmap;

t_uint					rgba_to_int(t_rgba color);
t_rgba					int_to_rgba(int color);
t_rgba					make_rgba(t_uchar r, t_uchar g, t_uchar b, t_uchar a);
t_rgba					get_pixel(t_bitmap bmp, t_uint x, t_uint y);
void					set_pixel(t_bitmap bmp, t_uint x, t_uint y,
									t_rgba color);
t_rect					rect(t_uint x, t_uint y, t_uint width, t_uint height);
void					fill_rect(t_bitmap bmp, t_rect rect, t_rgba color);

#endif
