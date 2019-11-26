/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debby <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 07:59:27 by debby             #+#    #+#             */
/*   Updated: 2020/05/24 14:01:49 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <sys/time.h>
#include <stdio.h>
#include "matrix.h"

/*
static t_vertex	p(t_vertex v, t_cam *cam, t_bitmap *bmp)
{
	t_vertex	projected;

	projected.vec = project(world.vec, cam, bmp);
	projected.col = world.col;
	return (projected);
}
*/

static t_vertex	p(t_vertex v, t_cam *cam)
{
	t_vertex	screen;

	screen.vec = to_screen(v.vec, cam->pipeline);
	screen.color = v.color;
	return (screen);
}

void			draw_map(t_bitmap bmp, t_cam *cam, const t_map *map,
				void (*draw_line)(t_bitmap, t_cam *, t_vertex, t_vertex))
{
	int			i;
	t_edge		prj;
	t_list		*row;

	row = map->rows;
	while (row)
	{
		i = 0;
		while (i < map->row_size)
		{
			prj.v1 = p(((t_vertex *)row->content)[i], cam);
			if (i < map->row_size - 1)
			{
				prj.v2 = p(((t_vertex *)row->content)[i + 1], cam);
				draw_line(bmp, cam, prj.v1, prj.v2);
			}
			if (row->next)
			{
				prj.v2 = p(((t_vertex *)row->next->content)[i], cam);
				draw_line(bmp, cam, prj.v1, prj.v2);
			}
			i++;
		}
		row = row->next;
	}
}
