/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:43:24 by qsharoly          #+#    #+#             */
/*   Updated: 2022/04/12 12:48:09 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

static int	color_gradient(float t, int bottom, int middle, int top)
{
	if (t >= .5)
		return (mix(top, middle, (1.0 - t) / (1.0 - 0.5)));
	else
		return (mix(middle, bottom, (0.5 - t) / (0.5 - 0.0)));
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
