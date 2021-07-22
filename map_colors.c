/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:43:24 by qsharoly          #+#    #+#             */
/*   Updated: 2021/07/22 15:10:18 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "color.h"

void			map_find_height_range(t_map *map)
{
	float		z;
	int			i;
	t_list		*rows;

	map->z_min = 0;
	map->z_max = 0;
	rows = map->rows;
	while (rows)
	{
		i = 0;
		while (i < map->row_size)
		{
			z = ((t_vertex *)rows->content)[i].vec.z;
			map->z_min = fmin(z, map->z_min);
			map->z_max = fmax(z, map->z_max);
			i++;
		}
		rows = rows->next;
	}
}

static int	color_from_z(float z, float z_min, float z_max)
{
	float	z_mid;

	z_mid = (z_max + z_min) / 2;
	if (z_max == z_min)
		return (LIGHTGREEN);
	else if (z >= z_mid)
		return (mix(PEACH, GRASS, (z_max - z) / (z_max - z_mid)));
	else
		return (mix(GRASS, PURPLE, (z_mid - z) / (z_mid - z_min)));
}

void			map_make_colors(t_map *map)
{
	int			i;
	t_vertex	*vert;
	t_list		*rows;

	rows = map->rows;
	while (rows)
	{
		i = 0;
		while (i < map->row_size)
		{
			vert = &((t_vertex *)rows->content)[i];
			vert->color = color_from_z(vert->vec.z, map->z_min, map->z_max);
			i++;
		}
		rows = rows->next;
	}
}
