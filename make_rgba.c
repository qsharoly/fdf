/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_rgba.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 16:39:53 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/06 16:43:12 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitmap.h"

t_rgba	make_rgba(t_uchar r, t_uchar g, t_uchar b, t_uchar a)
{
	t_rgba	col;

	col.r = r;
	col.g = g;
	col.b = b;
	col.a = a;
	return (col);
}
