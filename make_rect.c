/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 10:55:36 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/06 11:06:35 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitmap.h"

t_rect	rect(t_uint x, t_uint y, t_uint width, t_uint height)
{
	t_rect	r;

	r.x = x;
	r.y = y;
	r.width = width;
	r.height = height;
	return (r);
}
