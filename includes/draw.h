/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:31:20 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/12 16:44:18 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "bitmap.h"
# include "vector.h"
# include "vertex.h"
# include "projection.h"

t_rgba	mix(t_rgba col1, t_rgba col2, float ratio);
int		inbounds(t_float2 point, t_bitmap *bmp);
void	do_blend(t_bitmap *bmp, t_float2 p, t_rgba color);
void	draw_line(t_bitmap *bmp, t_float2 a, t_float2 b, t_rgba color);
void	draw_edge(t_bitmap *bmp, t_cam cam, t_float3 a, t_float3 b, t_rgba color);
void	draw_edge_gradient(t_bitmap *bmp, t_cam cam, t_vertex a, t_vertex b);

#endif
