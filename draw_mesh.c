/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:23:49 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/27 14:42:04 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vertex	p(t_vertex world, const t_cam *cam, t_bitmap bmp)
{
	t_vertex	screen;

	screen.vec = project(world.vec, cam, bmp);
	screen.col = world.col;
	return (screen);
}

void			draw_mesh(t_bitmap bmp, t_cam *cam, t_mesh mesh,
				int use_zbuf)
{
	int			i;
	void		(*draw_func)(t_bitmap, t_cam *, t_vertex, t_vertex);

	draw_func = use_zbuf ? draw_line_gradient_zbuf : draw_line_gradient;
	i = 0;
	while (i < mesh.len)
	{
		draw_func(bmp, cam, p(mesh.edges[i].v1, cam, bmp), p(mesh.edges[i].v2, cam, bmp));
		i++;
	}
}
