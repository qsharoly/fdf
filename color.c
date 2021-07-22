/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debby <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 15:05:51 by debby             #+#    #+#             */
/*   Updated: 2021/07/22 15:11:29 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include <math.h>

// mix: interpolate between colors
// ratio is expected to be in range [0.0, 1.0]
int mix(int ai, int bi, float ratio)
{
	t_argb	a;
	t_argb	b;
	t_argb	mix;

	a = int_to_rgba(ai);
	b = int_to_rgba(bi);
	mix.a = sqrt(a.a*a.a + (b.a*b.a - a.a*a.a) * ratio);
	mix.r = sqrt(a.r*a.r + (b.r*b.r - a.r*a.r) * ratio);
	mix.g = sqrt(a.g*a.g + (b.g*b.g - a.g*a.g) * ratio);
	mix.b = sqrt(a.b*a.b + (b.b*b.b - a.b*a.b) * ratio);
	return (rgba_to_int(mix));
}


int		rgba_to_int(t_argb color)
{
	int	out;

	out = color.a << 24;
	out += color.r << 16;
	out += color.g << 8;
	out += color.b << 0;
	return (out);
}

t_argb	int_to_rgba(int color)
{
	t_argb			argb;

	argb.a = (color & 0xff000000) >> 24;
	argb.r = (color & 0x00ff0000) >> 16;
	argb.g = (color & 0x0000ff00) >> 8;
	argb.b = (color & 0x000000ff) >> 0;
	return (argb);
}
