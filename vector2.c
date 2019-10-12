/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:40:03 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/12 16:53:34 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

float		squared(float a)
{
	return (a * a);
}

float		distance(t_float2 a, t_float2 b)
{
	return (sqrt(squared(a.x - b.x) + squared(a.y - b.y)));
}

t_float2	add_float2(t_float2 a, t_float2 b)
{
	t_float2	sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	return (sum);
}

t_float2	take_xy(t_float3 point)
{
	t_float2	xy;

	xy.x = point.x;
	xy.y = point.y;
	return (xy);
}
