/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:15:41 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/15 17:18:30 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTION_H
# define PROJECTION_H

# include "vector.h"
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
	t_float3		world;
	t_float3		dir;
	t_float3		up;
	t_float3		right;
	t_float3		proj_dir;
	t_float3		rot;
	float			dist;
	float			z_near;
	float			z_far;
	float			zoom;
	float			altitude_mult;
	float			*z_buf;
	t_uint			z_buf_size;
	t_uint			z_buf_stride;
	enum e_projkind	projection;
}				t_cam;

t_float3		project(t_float3 point, t_cam *cam, t_bitmap *bmp);
void			cam_setup_perspective(t_cam *cam);
void			cam_setup_axonometric(t_cam *cam);
void			cam_setup_military(t_cam *cam);
void			cam_setup_cavalier(t_cam *cam);
void			translate_cam(t_cam *cam, int command);

#endif
