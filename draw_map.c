/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:23:49 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/24 18:55:56 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vertex	p(t_vertex world, t_cam *cam, t_bitmap *bmp)
{
	t_vertex	screen;

	screen.vec = project(world.vec, cam, bmp);
	screen.col = world.col;
	return (screen);
}

void			draw_map(t_bitmap *bmp, t_cam *cam, t_map *map, t_list *rows)
{
	int			i;
	t_vertex	vertex1;
	t_vertex	vertex2;

	rows = map->rows;
	while (rows)
	{
		i = 0;
		while (i < map->row_size)
		{
			vertex1 = p(((t_vertex *)rows->content)[i], cam, bmp);
			if (i < map->row_size - 1)
			{
				vertex2 = p(((t_vertex *)rows->content)[i + 1], cam, bmp);
				draw_line_gradient(bmp, vertex1, vertex2);
			}
			if (rows->next)
			{
				vertex2 = p(((t_vertex *)rows->next->content)[i], cam, bmp);
				draw_line_gradient(bmp, vertex1, vertex2);
			}
			i++;
		}
		rows = rows->next;
	}
}

void			draw_map_z_buf(t_bitmap *bmp, t_cam *cam, t_map *map,
					t_list *rows)
{
	int			i;
	t_vertex	vertex1;
	t_vertex	vertex2;

	while (rows)
	{
		i = 0;
		while (i < map->row_size)
		{
			vertex1 = p(((t_vertex *)rows->content)[i], cam, bmp);
			if (i < map->row_size - 1)
			{
				vertex2 = p(((t_vertex *)rows->content)[i + 1], cam, bmp);
				draw_line_gradient_z_buf(bmp, cam, vertex1, vertex2);
			}
			if (rows->next)
			{
				vertex2 = p(((t_vertex *)rows->next->content)[i], cam, bmp);
				draw_line_gradient_z_buf(bmp, cam, vertex1, vertex2);
			}
			i++;
		}
		rows = rows->next;
	}
}
