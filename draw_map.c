/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:23:49 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/24 17:51:45 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(t_bitmap *bmp, t_cam *cam, t_map *map, int use_z_buf)
{
	int			i;
	t_list		*rows;
	t_vertex	vertex1;
	t_vertex	vertex2;
	void		(*draw_func)(t_bitmap *, t_cam *, t_vertex, t_vertex);

	draw_func = use_z_buf ? draw_line_gradient_z_buf : draw_line_gradient;
	rows = map->rows;
	while (rows)
	{
		i = 0;
		while (i < map->row_size)
		{
			vertex1 = ((t_vertex *)rows->content)[i];
			vertex1.vec = project(vertex1.vec, cam, bmp);
			if (i < map->row_size - 1)
			{
				vertex2 = ((t_vertex *)rows->content)[i + 1];
				vertex2.vec = project(vertex2.vec, cam, bmp);
				draw_func(bmp, cam, vertex1, vertex2);
			}
			if (rows->next)
			{
				vertex2 = ((t_vertex *)rows->next->content)[i];
				vertex2.vec = project(vertex2.vec, cam, bmp);
				draw_func(bmp, cam, vertex1, vertex2);
			}
			i++;
		}
		rows = rows->next;
	}
}
