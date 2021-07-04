/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:40:03 by qsharoly          #+#    #+#             */
/*   Updated: 2021/07/04 02:56:02 by debby            ###   ########.fr       */
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

t_vec2	add_vec2(t_vec2 a, t_vec2 b)
{
	t_vec2	sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	return (sum);
}
