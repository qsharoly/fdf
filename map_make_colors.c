/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_z_range.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:43:24 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/27 16:53:43 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "palette.h"

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
			map->z_min = ft_fmin(z, map->z_min);
			map->z_max = ft_fmax(z, map->z_max);
			i++;
		}
		rows = rows->next;
	}
}

static t_rgba	color_from_z(t_vec3 point,
					float z_min, float z_mid, float z_max)
{
	if (z_max == z_min)
		return (LIGHTGREEN);
	else if (point.z >= z_mid)
		return (mix(DARKGREEN, PEACH, (z_max - point.z) / (z_max - z_mid)));
	else
		return (mix(DARKGREEN, PURPLE, (z_min - point.z) / (z_min - z_mid)));
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
			vert->col = color_from_z(vert->vec, map->z_min,
					0.5 * (map->z_max + map->z_min), map->z_max);
			i++;
		}
		rows = rows->next;
	}
}
