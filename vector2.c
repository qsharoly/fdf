/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:40:03 by qsharoly          #+#    #+#             */
/*   Updated: 2021/06/30 17:45:04 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

float	squared(float a)
{
	return (a * a);
}

float len2(float ax, float ay, float bx, float by)
{
	return (sqrt(squared(ax - bx) + squared(ay - by)));
}

float	length2(t_vec2 a, t_vec2 b)
{
	return (sqrt(squared(a.x - b.x) + squared(a.y - b.y)));
}

t_vec2	add_vec2(t_vec2 a, t_vec2 b)
{
	t_vec2	sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	return (sum);
}
/*
t_vec2	take_xy(t_vec3 point)
{
	t_vec2	xy;

	xy.x = point.x;
	xy.y = point.y;
	return (xy);
}
*/
