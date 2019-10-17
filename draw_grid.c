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

void	draw_grid_z_buf(t_bitmap *bmp, t_cam *cam, t_list *rows)
{
	int			i;
	t_vertex	vertex1;
	t_vertex	vertex2;

	while (rows)
	{
		i = 0;
		while (i < (int)(rows->content_size / sizeof(t_vertex)))
		{
			vertex1 = ((t_vertex *)rows->content)[i];
			if (i < (int)(rows->content_size / sizeof(t_vertex)) - 1)
			{
				vertex2 = ((t_vertex *)rows->content)[i + 1];
				draw_edge_gradient_z_buf(bmp, cam, vertex1, vertex2);
			}
			if (rows->next
					&& i < (int)(rows->next->content_size / sizeof(t_vertex)))
			{
				vertex2 = ((t_vertex *)rows->next->content)[i];
				draw_edge_gradient_z_buf(bmp, cam, vertex1, vertex2);
			}
			i++;
		}
		rows = rows->next;
	}
}

void	draw_grid(t_bitmap *bmp, t_cam *cam, t_list *rows)
{
	int			i;
	t_vertex	vertex1;
	t_vertex	vertex2;

	while (rows)
	{
		i = 0;
		while (i < (int)(rows->content_size / sizeof(t_vertex)))
		{
			vertex1 = ((t_vertex *)rows->content)[i];
			if (i < (int)(rows->content_size / sizeof(t_vertex)) - 1)
			{
				vertex2 = ((t_vertex *)rows->content)[i + 1];
				draw_edge_gradient(bmp, cam, vertex1, vertex2);
			}
			if (rows->next
					&& i < (int)(rows->next->content_size / sizeof(t_vertex)))
			{
				vertex2 = ((t_vertex *)rows->next->content)[i];
				draw_edge_gradient(bmp, cam, vertex1, vertex2);
			}
			i++;
		}
		rows = rows->next;
	}
}
