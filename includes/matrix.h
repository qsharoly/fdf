/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 13:56:16 by qsharoly          #+#    #+#             */
/*   Updated: 2020/05/24 14:13:47 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"
# include "projection.h"

# define X 0
# define Y 1
# define Z 2
# define W 3

typedef struct	s_v4
{
	float	v[4];
}				t_vec4;

typedef	struct	s_m4
{
	float	m[4][4];
}				t_mat4;

float	dot4(float a[4], float b[4]);
t_vec4	point4(t_vec3 v);
t_vec4	direction4(t_vec3 v);
t_vec4	transform(t_mat4 m, t_vec4 v);
t_mat4	transpose(t_mat4 m);
t_mat4	compose(t_mat4 a, t_mat4 b);
t_mat4	zero_mat4(void);
t_mat4	identity_mat4(void);
t_mat4	translation_mat4(float x, float y, float z);
t_mat4	scaling_mat4(float x_scale, float y_scale, float z_scale);
t_mat4	rot_mat4_simple(char axis, float angle);
t_mat4	rot_mat4(t_vec3 dir, float angle);

#endif
