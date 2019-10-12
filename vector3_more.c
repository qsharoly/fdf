/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_more.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 14:28:45 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/12 14:33:36 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_float3	normalize(t_float3 vec)
{
	return (scalar_mul(vec, 1 / length3(vec)));
}
