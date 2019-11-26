/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:15:41 by qsharoly          #+#    #+#             */
/*   Updated: 2020/05/24 14:14:54 by debby            ###   ########.fr       */
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
	t_mat4			pipeline;
	t_vec3			target;
	t_vec3			dir;
	t_vec3			up;
	t_vec3			right;
	t_vec3			proj_dir;
	t_vec3			angle;
	float			dist;
	float			z_near;
	float			z_far;
	float			fov;
	float			zoom;
	float			altitude_mult;
	float			*zbuf;
	t_uint			zbuf_size;
	t_uint			zbuf_stride;
	enum e_projkind	projection;
}				t_cam;

t_vec3		project(t_vec3 point, const t_cam *cam, t_bitmap bmp);
void		cam_setup_perspective(t_cam *cam);
void		cam_setup_axonometric(t_cam *cam);
void		cam_setup_military(t_cam *cam);
void		cam_setup_cavalier(t_cam *cam);
void		translate_cam(t_cam *cam, int command);
t_mat4		perspective_mat4(t_cam *cam, t_bitmap bmp);
t_mat4		orthographic_mat4(t_cam *cam, t_bitmap bmp);
t_vec3		persp_divide(t_vec4 v);
void		calc_pipeline(t_cam *cam, t_bitmap bmp);
t_vec3		to_screen(t_vec3 point, t_mat4 pipeline);

#endif
