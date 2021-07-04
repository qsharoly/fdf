/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debby <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 07:59:27 by debby             #+#    #+#             */
/*   Updated: 2021/07/03 01:11:36 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <sys/time.h>
#include <stdio.h>
#include "matrix.h"

void	apply_transform(t_vertex *res, t_map *map, t_cam *cam)
{
	const t_list	*row;
	t_vertex		v;
	int				i;
	int				j;

	row = map->rows;
	j = 0;
	while (j < map->row_num)
	{
		i = 0;
		while (i < map->row_size)
		{
			v = ((t_vertex *)row->content)[i];
			res[j * map->row_size + i].vec = geom_to_pixel(v.vec, cam);
			res[j * map->row_size + i].color = v.color;
			i++;
		}
		row = row->next;
		j++;
	}
}

void	draw_map(t_bitmap bmp, t_cam *cam, const t_map *map,
				void (*line2d)(t_bitmap, t_cam *, t_vertex, t_vertex))
{
	int			i;
	int			j;
	t_vertex	v1;
	t_vertex	v2;

	j = 0;
	while (j < map->row_num)
	{
		i = 0;
		while (i < map->row_size)
		{
			v1 = map->projected[j * map->row_size + i];
			if (i < map->row_size - 1)
			{
				v2 = map->projected[j * map->row_size + i + 1];
				line2d(bmp, cam, v1, v2);
			}
			if (j < map->row_num - 1)
			{
				v2 = map->projected[(j + 1) * map->row_size + i];
				line2d(bmp, cam, v1, v2);
			}
			i++;
		}
		j++;
	}
}
