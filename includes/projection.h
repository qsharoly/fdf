/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:15:41 by qsharoly          #+#    #+#             */
/*   Updated: 2021/07/02 09:57:46 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTION_H
# define PROJECTION_H

# include "vector.h"
# include "matrix.h"
# include "bitmap.h"

# define N_PROJECTION_KINDS 4
# define GO_FWD 0
# define GO_BACK 1
# define STRAFE_RIGHT 2
# define STRAFE_LEFT 3

enum			e_projkind
{
	Perspective,
	Axonometric,
	Oblique_Military,
	Oblique_Cavalier
};

typedef struct	s_cam
{
	t_mat4			matrix;
	t_vec3			target;
	t_vec3			angle;
	float			dist;
	float			z_near;
	float			z_far;
	float			fov;
	float			zoom;
	float			aspect;
	float			altitude_scale;
	float			*zbuf;
	t_uint			zbuf_size;
	t_uint			zbuf_stride;
	enum e_projkind	projection;
}				t_cam;

void		cam_walk(t_cam *cam, int direction);
void		cam_drag(t_cam *cam, float dx, float dy);
void		calc_camera_transform(t_cam *cam);
t_vec3		geom_to_pixel(t_vec3 point, const t_cam *cam);

#endif
