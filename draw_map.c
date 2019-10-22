/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:23:49 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/17 15:36:56 by qsharoly         ###   ########.fr       */
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

	draw_func = use_z_buf ? draw_edge_gradient_z_buf : draw_edge_gradient;
	rows = map->rows;
	while (rows)
	{
		i = 0;
		while (i < map->row_size)
		{
			vertex1 = ((t_vertex *)rows->content)[i];
			if (i < map->row_size - 1)
			{
				vertex2 = ((t_vertex *)rows->content)[i + 1];
				draw_func(bmp, cam, vertex1, vertex2);
			}
			if (rows->next
					&& i < map->row_size) 
			{
				vertex2 = ((t_vertex *)rows->next->content)[i];
				draw_func(bmp, cam, vertex1, vertex2);
			}
			i++;
		}
		rows = rows->next;
	}
}
