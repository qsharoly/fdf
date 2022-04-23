/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debby <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 07:59:27 by debby             #+#    #+#             */
/*   Updated: 2022/04/23 21:45:08 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "matrix.h"

void	transform_vertices_v2(t_vertex *result, const t_vertex *vertices, int vertices_size, t_cam *cam)
{
	int				i;

	i = 0;
	while (i < vertices_size)
	{
		result[i] = (t_vertex){
			.vec = geom_to_pixel(vertices[i].vec, cam),
			.color_id = vertices[i].color_id
		};
		i++;
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
