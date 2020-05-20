/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_mesh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debby <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 04:38:41 by debby             #+#    #+#             */
/*   Updated: 2020/05/20 05:39:35 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		construct_mesh(t_mesh *mesh, const t_map *map)
{
	t_list		*row;
	t_vertex	common;
	int			i;
	int			len;

	mesh->edges = malloc(sizeof(t_edge)
					* ((map->row_size - 1) * map->row_num
						+ (map->row_num - 1) * map->row_size));
	if (!mesh->edges)
		return (fail("failed to malloc mesh edges\n"));
	len = 0;
	row = map->rows;
	while (row)
	{
		i = 0;
		while (i < map->row_size)
		{
			common = ((t_vertex *)row->content)[i];
			if (i < map->row_size - 1)
			{
				mesh->edges[len].v1 = common;
				mesh->edges[len].v2 = ((t_vertex *)row->content)[i + 1];
				len++;
			}
			if (row->next)
			{
				mesh->edges[len].v1 = common;
				mesh->edges[len].v2 = ((t_vertex *)row->next->content)[i];
				len++;
			}
			i++;
		}
		row = row->next;
	}
	mesh->len = len;
	return (GOOD);
}
