/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:31:20 by qsharoly          #+#    #+#             */
/*   Updated: 2022/04/12 14:07:48 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "bitmap.h"
# include "vector.h"
# include "camera.h"

typedef struct	s_vertex
{
	t_vec3	vec;
	float	color_id;
}				t_vertex;

typedef struct	s_edge
{
	unsigned int	start;
	unsigned int	end;
}				t_edge;

typedef struct	s_zbuffer
{
	float	*z;
	int		stride;
	int		size;
}				t_zbuffer;

typedef struct	s_view
{
	t_bitmap	bmp;
	t_cam		*cam;
}				t_view;

int				inbounds(float x, float y, t_bitmap bmp);
int				inbounds3(t_vec3 point, t_bitmap bmp, const t_cam *cam);
void			line_solid(t_bitmap bmp, t_vec3 a, t_vec3 b, int color);
void			line_gradient(t_bitmap bmp, void *cam, t_vertex a, t_vertex b);
void			line_gradient_zbuf(t_bitmap bmp, void *zb, t_vertex a, t_vertex b);
void			reset_zbuf(t_zbuffer *zb);

#endif
