/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:31:20 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/24 18:52:32 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "bitmap.h"
# include "vector.h"
# include "vertex.h"
# include "projection.h"

typedef struct	s_view
{
	t_bitmap	*bmp;
	t_cam		*cam;
}				t_view;

t_rgba			mix(t_rgba col1, t_rgba col2, float ratio);
int				inbounds(t_float2 point, t_bitmap *bmp);
int				inbounds3(t_float3 point, t_bitmap *bmp, t_cam *cam);
void			draw_line(t_bitmap *bmp, t_float2 a, t_float2 b, t_rgba color);
void			draw_edge(t_view view, t_float3 a, t_float3 b, t_rgba color);
void			draw_line_gradient(t_bitmap *bmp, t_cam * cam,
					t_vertex a, t_vertex b);
void			draw_line_gradient_z_buf(t_bitmap *bmp, t_cam *cam,
					t_vertex a, t_vertex b);
void			reset_z_buf(t_cam *cam);

#endif
