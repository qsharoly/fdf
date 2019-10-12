/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:33:25 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/12 16:24:23 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_float3	add_float3(t_float3 a, t_float3 b)
{
	t_float3	sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	sum.z = a.z + b.z;
	return (sum);
}

float		dot(t_float3 a, t_float3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_float3	cross(t_float3 a, t_float3 b)
{
	t_float3	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

t_float3	scalar_mul(t_float3 vec, float s)
{
	vec.x *= s;
	vec.y *= s;
	vec.z *= s;
	return (vec);
}

float		length3(t_float3 vec)
{
	return (sqrt(dot(vec, vec)));
}
