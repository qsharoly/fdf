/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:27:49 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/15 17:18:29 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct	s_float2
{
	float	x;
	float	y;
}				t_float2;
typedef struct	s_float3
{
	float	x;
	float	y;
	float	z;
}				t_float3;

# define ORIGIN (t_float3) {0.0, 0.0, 0.0}
# define XUNIT (t_float3) {1.0, 0.0, 0.0}
# define YUNIT (t_float3) {0.0, 1.0, 0.0}
# define ZUNIT (t_float3) {0.0, 0.0, 1.0}

float			squared(float a);
float			distance(t_float2 a, t_float2 b);
t_float2		add_float2(t_float2 a, t_float2 b);
t_float2		take_xy(t_float3 point);
t_float3		add_float3(t_float3 a, t_float3 b);
t_float3		sub_float3(t_float3 a, t_float3 b);
float			dot(t_float3 a, t_float3 b);
t_float3		cross(t_float3 a, t_float3 b);
t_float3		scalar_mul(t_float3 vec, float s);
float			length3(t_float3 vec);
t_float3		normalize(t_float3 vec);
t_float3		make_float3(float x, float y, float z);
t_float3		rot_x(float angle, t_float3 vec);
t_float3		rot_y(float angle, t_float3 vec);
t_float3		rot_z(float angle, t_float3 vec);

#endif
