/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 14:23:06 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/12 14:23:41 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

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
