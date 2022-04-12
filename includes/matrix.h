/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 13:56:16 by qsharoly          #+#    #+#             */
/*   Updated: 2022/04/12 14:07:42 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"
# include "camera.h"

# define X 0
# define Y 1
# define Z 2
# define W 3

typedef float	t_vec4[4];
typedef float	t_mat4[4][4];

float	dot4(const t_vec4 a, const t_vec4 b);
void	point4(t_vec4 tgt, t_vec3 v);
void	direction4(t_vec4 tgt, t_vec3 v);
void	transform(const t_mat4 m, t_vec4 v);
void	compose(t_mat4 a, const t_mat4 b);
void	zero_mat4(t_mat4 m);
void	identity_mat4(t_mat4 m);
void	translation_mat4(t_mat4 m, float x, float y, float z);
void	scaling_mat4(t_mat4 m, float x_scale, float y_scale, float z_scale);
void	rot_mat4_simple(t_mat4 m, char axis, float angle);
void	rot_mat4(t_mat4 m, t_vec3 dir, float angle);

#endif
