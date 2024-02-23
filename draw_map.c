/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debby <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 07:59:27 by debby             #+#    #+#             */
/*   Updated: 2024/02/23 11:06:58 by kith             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	transform_vertices(t_vertex *result, const t_vertex *vertices,
		int vertices_size, const t_cam *cam, int x_dim, int y_dim)
{
	int				i;

	i = 0;
	while (i < vertices_size)
	{
		result[i] = (t_vertex){
			.vec = geom_to_pixel(vertices[i].vec, cam, x_dim, y_dim),
			.altitude = vertices[i].altitude
		};
		i++;
	}
}

int	is_inside(t_vec3 a, int x_dim, int y_dim)
{
	return (0.0 <= a.x && a.x < x_dim && 0.0 <= a.y && a.y < y_dim);
}

//stackoverflow.com//questions/4977491/determining-if-two-line-segments-intersect/4977569#4977569
static int	segments_intersect(t_vec3 a, t_vec3 b, t_vec3 c, t_vec3 d,
				t_vec3 *intersection)
{
	// z is used only for interpolation when intersection is found
	t_vec3 ab = (t_vec3){b.x - a.x, b.y - a.y, b.z - a.z};
	t_vec3 cd = (t_vec3){d.x - c.x, d.y - c.y, d.z - c.z};
	float det = cd.x * ab.y - ab.x * cd.y;
	if (det == 0)
		return 0;
	float s = (1/det) * ((a.x - c.x) * ab.y - (a.y - c.y) * ab.x);
	float t = (1/det) * -(-(a.x - c.x) * cd.y + (a.y - c.y) * cd.x);
	if (0 <= s && s <= 1 && 0 <= t && t <= 1)
	{
		if (intersection != NULL)
		{
			(*intersection).x = a.x + t * ab.x;
			(*intersection).y = a.y + t * ab.y;
			(*intersection).z = a.z + t * ab.z;
		}
		return 1;
	}
	return 0;
}

//#include <stdio.h>
// returns 0 if segment is fully outside
static int	clamp(t_vertex *ap, t_vertex *bp, int xmax, int ymax)
{
	t_vec3 a = ap->vec;
	t_vec3 b = bp->vec;

	// these definitely do not intersect
	if ((a.x < 0 && b.x < 0) || (a.x >= xmax && b.x >= xmax)
			|| (a.y < 0 && b.y < 0) || (a.y >= ymax && b.y >= ymax))
		return (0);

	int a_in = is_inside(a, xmax, ymax);
	int b_in = is_inside(b, xmax, ymax);
	if (a_in && b_in)
		return (1);
	t_vec3	ul = (t_vec3){0, 0, 0};
	t_vec3	ur = (t_vec3){xmax-1, 0, 0};
	t_vec3	dl = (t_vec3){0, ymax-1, 0};
	t_vec3	dr = (t_vec3){xmax-1, ymax-1, 0};
	if (a_in)
	{
		//printf("b");
		t_vec3	inter;
		if (segments_intersect(a, b, ul, ur, &inter))
		{
			bp->vec = inter;
			return (1);
		}
		else if (segments_intersect(a, b, ul, dl, &inter))
		{
			bp->vec = inter;
			return (1);
		}
		else if (segments_intersect(a, b, dl, dr, &inter))
		{
			bp->vec = inter;
			return (1);
		}
		else if (segments_intersect(a, b, dr, ur, &inter))
		{
			bp->vec = inter;
			return (1);
		}
		//dprintf(2, "bad a_in\n");
		return (0);
	}
	else if (b_in)
	{
		//printf("a");
		t_vec3	inter;
		if (segments_intersect(a, b, ul, ur, &inter))
		{
			ap->vec = inter;
			return (1);
		}
		else if (segments_intersect(a, b, ul, dl, &inter))
		{
			ap->vec = inter;
			return (1);
		}
		else if (segments_intersect(a, b, dl, dr, &inter))
		{
			ap->vec = inter;
			return (1);
		}
		else if (segments_intersect(a, b, dr, ur, &inter))
		{
			ap->vec = inter;
			return (1);
		}
		//dprintf(2, "bad b_in a:%f %f b:%f %f\n",a.x, a.y, b.x, b.y);
		return (0);
	}
	else
	{
		//printf("2");
		//both a and b are out, but the middle part of the segment
		//may still intersect with the rectangle.

		t_vec3	intersections[4];
		int found = 0;
		found += segments_intersect(a, b, ul, ur, &intersections[found]);
		found += segments_intersect(a, b, ur, dr, &intersections[found]);
		found += segments_intersect(a, b, dr, dl, &intersections[found]);
		found += segments_intersect(a, b, dl, ul, &intersections[found]);
		if (found == 2)
		{
			ap->vec = intersections[0];
			bp->vec = intersections[1];
			//fixup inverted order of points
			if ((b.x - a.x) * (bp->x - ap->x) < 0
				&& (b.y - a.y) * (bp->y - ap->y) < 0)
			{
				//dprintf(2, "inverted!\n");
				t_vec3 tmp = ap->vec;
				ap->vec = bp->vec;
				bp->vec = tmp;
			}
			return (1);
		}
		else if (found == 0)
		{
			//no intersection
			return (0);
		}
		//dprintf(2, "bad: must have 2 or 0 intersections when both points are out!\n");
		return (0);
	}
	//never get here
	return (0);
}

void	draw_edges(t_bitmap bmp, const t_vertex *verts,
			const t_edge *edges, int edges_size)
{
	int	i;

	i = 0;
	while (i < edges_size)
	{
		t_vertex a = verts[edges[i].start];
		t_vertex b = verts[edges[i].end];
		if (clamp(&a, &b, bmp.x_dim, bmp.y_dim))
			line_gradient(bmp, a, b);
		i++;
	}
}

void	draw_edges_zbuf(t_bitmap bmp, t_zbuffer zb, const t_vertex *verts,
			const t_edge *edges, int edges_size)
{
	int	i;

	i = 0;
	while (i < edges_size)
	{
		t_vertex a = verts[edges[i].start];
		t_vertex b = verts[edges[i].end];
		if (clamp(&a, &b, bmp.x_dim, bmp.y_dim))
			line_gradient_zbuf(bmp, zb.z, a, b);
		i++;
	}
}
