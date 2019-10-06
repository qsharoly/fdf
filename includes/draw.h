/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:31:20 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/06 10:50:19 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "bitmap.h"
# include "vector.h"

t_rgba	mix(t_rgba col1, t_rgba col2, float ratio);
int		inbounds(t_float2 point, t_bitmap *bmp);
void	do_blend(t_bitmap *bmp, t_float2 p, t_rgba color);
void	draw_line(t_bitmap *bmp, t_float2 a, t_float2 b, t_rgba color);
void	draw_line_gradient(t_bitmap *bmp, t_float2 a, t_float2 b,
							t_rgba a_color, t_rgba b_color);

#endif
