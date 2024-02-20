/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debby <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 15:05:51 by debby             #+#    #+#             */
/*   Updated: 2022/11/07 09:22:42 by kith             ###   ########.fr       */
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

	a = int_to_argb(ai);
	b = int_to_argb(bi);
	mix.a = sqrt(a.a*a.a + (b.a*b.a - a.a*a.a) * ratio);
	mix.r = sqrt(a.r*a.r + (b.r*b.r - a.r*a.r) * ratio);
	mix.g = sqrt(a.g*a.g + (b.g*b.g - a.g*a.g) * ratio);
	mix.b = sqrt(a.b*a.b + (b.b*b.b - a.b*a.b) * ratio);
	return (argb_to_int(mix));
}

#if INTEL
#include <xmmintrin.h>
#include <stdalign.h>
int mix_2(int ai, int bi, float ratio_in)
{
	__m128i a_argb = _mm_set_epi32((ai&0xff000000)>>24, (ai&0x00ff0000)>>16,
								(ai&0x0000ff00)>>8, (ai&0x000000ff));
	__m128i b_argb = _mm_set_epi32((bi&0xff000000)>>24, (bi&0x00ff0000)>>16,
								(bi&0x0000ff00)>>8, (bi&0x000000ff));


	__m128 a = _mm_cvtepi32_ps(a_argb);
	__m128 b = _mm_cvtepi32_ps(b_argb);
	__m128 ratio = _mm_load_ps1(&ratio_in);
	a = _mm_mul_ps(a, a);
	b = _mm_mul_ps(b, b);
	__m128 mix = _mm_sub_ps(b, a);
	mix = _mm_mul_ps(mix, ratio);
	mix = _mm_add_ps(a, mix);
	mix = _mm_sqrt_ps(mix);
	/*
	__m128i conv = _mm_cvtps_epi32(mix);
	alignas(16) int extract[4];
	_mm_store_si128((__m128i*)extract, conv);
	int pack = (extract[3]&0xff)<<24
				| (extract[2]&0xff)<<16
				| (extract[1]&0xff)<<8
				| (extract[0]&0xff);
	*/
	alignas(16) float *extract = (float *)&mix;
	int pack = ((int)extract[3]&0xff)<<24
				| ((int)extract[2]&0xff)<<16
				| ((int)extract[1]&0xff)<<8
				| ((int)extract[0]&0xff);
	return (pack);
}
#endif //INTEL


int		argb_to_int(t_argb color)
{
	int	out;

	out = color.a << 24 | color.r << 16 | color.g << 8 | color.b;
	return (out);
}

t_argb	int_to_argb(int color)
{
	t_argb			argb;

	argb.a = (color & 0xff000000) >> 24;
	argb.r = (color & 0x00ff0000) >> 16;
	argb.g = (color & 0x0000ff00) >> 8;
	argb.b = (color & 0x000000ff) >> 0;
	return (argb);
}

int	color_gradient(float t, int bottom_color, int middle_color, int top_color)
{
	if (t >= .5)
		return (mix(top_color, middle_color, (1.0 - t) / (1.0 - 0.5)));
	else
		return (mix(middle_color, bottom_color, (0.5 - t) / (0.5 - 0.0)));
}

void	init_color_table(int table[COLOR_TABLE_SIZE])
{
	int		i;

	i = 0;
	while (i < COLOR_TABLE_SIZE)
	{
		table[i] = color_gradient((float)i / (float)COLOR_TABLE_SIZE, PURPLE, GRASS, PEACH);
		i++;
	}
}
