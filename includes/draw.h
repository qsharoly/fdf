/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:31:20 by qsharoly          #+#    #+#             */
/*   Updated: 2020/05/20 06:05:12 by debby            ###   ########.fr       */
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
	t_bitmap	bmp;
	t_cam		*cam;
}				t_view;

t_rgba			mix(t_rgba col1, t_rgba col2, float ratio);
int				inbounds(t_vec2 point, t_bitmap bmp);
int				inbounds3(t_vec3 point, t_bitmap bmp, const t_cam *cam);
void			draw_line(t_bitmap bmp, t_vec2 a, t_vec2 b, t_rgba color);
void			draw_edge(t_view view, t_vec3 a, t_vec3 b, t_rgba color);
void			draw_line_gradient(t_bitmap bmp, t_cam *cam,
					t_vertex a, t_vertex b);
void			draw_line_gradient_zbuf(t_bitmap bmp, t_cam *cam,
					t_vertex a, t_vertex b);
void			reset_zbuf(t_cam *cam);

#endif
