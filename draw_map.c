/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debby <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 07:59:27 by debby             #+#    #+#             */
/*   Updated: 2022/04/23 10:59:31 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <sys/time.h>
#include <stdio.h>
#include "matrix.h"

void	transform_vertices(t_vertex *result, t_map *map, t_cam *cam)
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
			result[j * map->row_size + i].vec = geom_to_pixel(v.vec, cam);
			result[j * map->row_size + i].color_id = v.color_id;
			i++;
		}
		row = row->next;
		j++;
	}
}

void	draw_map(t_bitmap bmp, t_zbuffer zb, t_vertex *verts, t_edge *edges, int edges_size,
				t_line_func line)
{
	int	i;

	i = 0;
	while (i < edges_size)
	{
		line(bmp, &zb, verts[edges[i].start], verts[edges[i].end]);
		i++;
	}
}
