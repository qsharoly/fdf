/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:33:25 by qsharoly          #+#    #+#             */
/*   Updated: 2022/04/28 20:43:35 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	add3(t_vec3 a, t_vec3 b)
{
	t_vec3	sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	sum.z = a.z + b.z;
	return (sum);
}

t_vec3	sub3(t_vec3 a, t_vec3 b)
{
	t_vec3	diff;

	diff.x = a.x - b.x;
	diff.y = a.y - b.y;
	diff.z = a.z - b.z;
	return (diff);
}

float	dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	cross(t_vec3 a, t_vec3 b)
{
	t_vec3	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

t_vec3	scale(t_vec3 vec, float s)
{
	vec.x *= s;
	vec.y *= s;
	vec.z *= s;
	return (vec);
}

float	length3(t_vec3 vec)
{
	return (sqrt(dot(vec, vec)));
}

t_vec3	normalize3(t_vec3 vec)
{
	return (scale(vec, 1 / length3(vec)));
}

t_vec3	rot_x(float angle, t_vec3 vec)
{
	t_vec3	rot;

	rot.x = vec.x;
	rot.y = cos(angle) * vec.y - sin(angle) * vec.z;
	rot.z = sin(angle) * vec.y + cos(angle) * vec.z;
	return (rot);
}

t_vec3	rot_y(float angle, t_vec3 vec)
{
	t_vec3	rot;

	rot.x = cos(angle) * vec.x - sin(angle) * vec.z;
	rot.y = vec.y;
	rot.z = sin(angle) * vec.x + cos(angle) * vec.z;
	return (rot);
}

t_vec3	rot_z(float angle, t_vec3 vec)
{
	t_vec3	rot;

	rot.x = cos(angle) * vec.x - sin(angle) * vec.y;
	rot.y = sin(angle) * vec.x + cos(angle) * vec.y;
	rot.z = vec.z;
	return (rot);
}
