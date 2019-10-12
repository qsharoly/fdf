/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_vertex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:16:48 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/12 17:18:57 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vertex.h"

t_vertex	mkvrtx(t_float3 vec, t_rgba color)
{
	t_vertex	vrtx;

	vrtx.vec = vec;
	vrtx.col = color;
	return (vrtx);
}
