/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_z_range.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:43:24 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/06 16:39:42 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

/*
** the list mesh->rows contains arrays of t_vertex.
** find minimal and maximal z values of all vertices and put them
** to corresponding structure items mesh->z_min and mesh->z_max
*/

void	grid_make_properties(t_grid *mesh)
{
	float		z;
	int			i;
	int			row_size;
	t_list		*rows;

	mesh->z_min = 0;
	mesh->z_max = 0;
	mesh->max_row_size = 0;
	rows = mesh->rows;
	while (rows)
	{
		i = 0;
		row_size = rows->content_size / sizeof(t_vertex);
		while (i < row_size)
		{
			z = ((t_vertex *)rows->content)[i].vec.z;
			mesh->z_min = ft_fmin(z, mesh->z_min);
			mesh->z_max = ft_fmax(z, mesh->z_max);
			mesh->max_row_size = ft_fmax(row_size, mesh->max_row_size);
			i++;
		}
		rows = rows->next;
	}
}

t_rgba		color_from_z(t_float3 point, float z_min, float z_max)
{
	t_rgba	high;
	t_rgba	low;
	t_rgba	inferno;

	high = make_rgba(150, 100, 250, 0);
	low = make_rgba(100, 250, 150, 0);
	inferno = make_rgba(250, 150, 100, 0);
	if (z_max == z_min)
		return (low);
	else
		if (point.z >= 0)
			return (mix(low, high, (z_max - point.z) / z_max));
		else
			return (mix(low, inferno, (point.z - z_min) / -z_min));
}

void	assign_colors_from_z(t_grid *mesh)
{
	int			i;
	int			row_size;
	t_vertex	*vert;
	t_list		*rows;

	rows = mesh->rows;
	while (rows)
	{
		i = 0;
		row_size = rows->content_size / sizeof(t_vertex);
		while (i < row_size)
		{
			vert = &((t_vertex *)rows->content)[i];
			vert->col = color_from_z(vert->vec, mesh->z_min, mesh->z_max);
			i++;
		}
		rows = rows->next;
	}
}
