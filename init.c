/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:18:34 by qsharoly          #+#    #+#             */
/*   Updated: 2022/04/23 20:33:53 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "fdf.h"
#include "settings.h"

void	log_failure(const char *msg)
{
	ft_putstr_fd(msg, 2);
}

t_state		init_state(void)
{
	t_state	state;

	state = (t_state){
		.dragging = 0,
		.bench_max_frames = BENCHMARK_FRAMES,
		.bench = 0,
		.stop_program = 0,
		.animation_running = 0,
		.animation_step = 0,
		.redraw = 1,
		.print_keycodes = 0,
		.draw_stats = 1,
		.draw_helpers = 1,
		.draw_controls = 0,
		.use_zbuf = 1,
		.time_stats = (t_time_stats){ .min_drawing_usec = +INFINITY },
	};
	return (state);
}

int		init_zbuffer(t_things *things)
{
	t_zbuffer	zb;

	zb.size = things->bitmap.x_dim * things->bitmap.y_dim;
	zb.stride = things->bitmap.x_dim;
	zb.z = malloc(sizeof(*zb.z) * zb.size);
	if (!zb.z)
	{
		log_failure("failed to malloc z-buffer\n");
		return (FAIL);
	}
	things->zbuffer = zb;
	return (OK);
}

t_cam	init_cam(int window_x_dim, int window_y_dim, const t_map *map)
{
	t_cam	cam;
	float	dist;

	dist = fmax(map->rows, map->per_row);
	cam = (t_cam){
		.target = {
			.x = map->per_row / 2,
			.y = map->rows / 2,
			.z = (map->z_min + map->z_max) / 2
		},
		.dist = dist,
		.zoom = 1,
		.z_near = 1,
		.z_far = 2 * dist,
		.fov = 0.5 * M_PI,
		.aspect = (float)window_y_dim / window_x_dim,
		.angle = ORIGIN,
		.projection = Perspective,
		.altitude_scale = 1
	};
	return (cam);
}

static void	map_assign_colors(t_map *map)
{
	int		i;
	float	z;
	float	relative_z;

	i = 0;
	while (i < map->rows * map->per_row)
	{
		z = map->vertices[i].vec.z;
		relative_z = ((z - map->z_min) / (map->z_max - map->z_min));
		map->vertices[i].color_id = (COLOR_TABLE_SIZE - 1) * relative_z;
		i++;
	}
}

static void	map_make_edges(t_edge **edgesptr, int *size, int map_per_row, int map_rows)
{
	int	i;
	int	j;
	int	current;
	t_edge *edges;
	
	*size = (map_per_row - 1) * map_rows + map_per_row * (map_rows - 1);

	(*edgesptr) = malloc(*size * sizeof(*edges));
	edges = *edgesptr;
	current = 0;
	j = 0;
	while (j < map_rows)
	{
		i = 0;
		while (i < map_per_row)
		{
			if (i < map_per_row - 1)
			{
				edges[current].start = i + j * map_per_row;
				edges[current].end = (i + 1) + j * map_per_row;
				current++;
			}
			if (j < map_rows - 1)
			{
				edges[current].start = i + j * map_per_row;
				edges[current].end = i + (j + 1) * map_per_row;
				current++;
			}
			i++;
		}
		j++;
	}
}

int		init_map(t_map *map, const char *filename)
{
	int	status;

	status = load_map_v2(filename, map);
	if (status == FAIL)
		return (FAIL);
	map_assign_colors(map);
	map->projected = malloc(map->per_row * map->rows * sizeof(*map->projected));
	map_make_edges(&map->edges, &map->edges_size, map->per_row, map->rows);
	return (OK);
}

int		init_bitmap(t_bitmap *bitmap, const void *mlx_img_ptr, int x_dim, int y_dim)
{
	int			bpp;
	int			stride;
	int			endianness;

	bitmap->data = (unsigned int *)mlx_get_data_addr((void *)mlx_img_ptr,
			&bpp, &stride, &endianness);
	if (!bitmap->data)
	{
		log_failure("falied to get image data address\n");
		return (FAIL);
	}
	bitmap->x_dim = x_dim;
	bitmap->y_dim = y_dim;
	return (OK);
}
