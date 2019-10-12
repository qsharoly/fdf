/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:15:41 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/12 16:53:49 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTION_H
# define PROJECTION_H

# include "vector.h"
# include "bitmap.h"

# define N_PROJECTION_KINDS 3

enum			e_projkind
{
	Axonometric,
	Oblique_Military,
	Oblique_Cavalier
};

typedef struct	s_cam
{
	t_float3	world;
	t_float3	dir;
	t_float3	up;
	t_float3	right;
	t_float3	proj_dir;
	float		dist;
	float		fov;
	float		altitude_mult;
	float		max_depth;
}				t_cam;

t_float3		project(t_float3 point, t_cam cam, t_bitmap *bmp);

#endif
