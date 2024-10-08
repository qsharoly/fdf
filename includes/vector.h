/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:27:49 by qsharoly          #+#    #+#             */
/*   Updated: 2022/04/28 17:00:38 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct	s_vec2
{
	float	x;
	float	y;
}				t_vec2;
typedef struct	s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

# define ORIGIN (t_vec3) {0.0, 0.0, 0.0}
# define XUNIT (t_vec3) {1.0, 0.0, 0.0}
# define YUNIT (t_vec3) {0.0, 1.0, 0.0}
# define ZUNIT (t_vec3) {0.0, 0.0, 1.0}

t_vec3		add3(t_vec3 a, t_vec3 b);
t_vec3		sub3(t_vec3 a, t_vec3 b);
float		dot(t_vec3 a, t_vec3 b);
t_vec3		cross(t_vec3 a, t_vec3 b);
t_vec3		scale(t_vec3 vec, float s);
float		length3(t_vec3 vec);
t_vec3		normalize3(t_vec3 vec);
t_vec3		vec3(float x, float y, float z);
t_vec3		rot_x(float angle, t_vec3 vec);
t_vec3		rot_y(float angle, t_vec3 vec);
t_vec3		rot_z(float angle, t_vec3 vec);

#endif
