/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:18:34 by qsharoly          #+#    #+#             */
/*   Updated: 2022/04/12 13:19:39 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "mlx.h"
#include "fdf.h"
#include "settings.h"
#include <math.h>

int			fail(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (FAIL);
}

t_state		init_state(void)
{
	t_state	state;

	state.dragging = 0;
	state.bench_max_frames = BENCHMARK_FRAMES;
	state.bench = 0;
	state.stop_program = 0;
	state.animation_running = 0;
	state.animation_step = 0;
	state.redraw = 1;
	state.print_keycodes = 0;
	state.draw_stats = 1;
	state.draw_helpers = 1;
	state.draw_controls = 0;
	state.use_zbuf = 1;
	return (state);
}

int		init_zbuffer(t_things *things)
{
	t_zbuffer	zb;

	zb.size = things->bitmap.x_dim * things->bitmap.y_dim;
	zb.stride = things->bitmap.x_dim;
	zb.z = malloc(sizeof(*zb.z) * zb.size);
	if (!zb.z)
		return (fail("failed to malloc z-buffer\n"));
	things->zbuffer = zb;
	return (OK);
}

int		init_cam(t_cam *cam, t_things *things)
{
	if (things->map.rows != NULL)
	{
		cam->target.x = things->map.row_size / 2;
		cam->target.y = things->map.row_num / 2;
		cam->target.z = (things->map.z_min + things->map.z_max) / 2;
		cam->dist = fmax(things->map.row_size, things->map.row_num);
		cam->zoom = 1;
	}
	cam->z_near = 1;
	cam->z_far = 2 * cam->dist;
	cam->fov = 0.5 * M_PI;
	cam->aspect = (float)things->bitmap.y_dim / things->bitmap.x_dim;
	cam->angle = ORIGIN;
//	cam->angle = (t_vec3){M_PI / 3, 0, M_PI / 4};
	cam->projection = Perspective;
	cam->altitude_scale = 1;
	return (OK);
}

static void	map_assign_colors(t_map *map)
{
	int			i;
	t_list		*rows;

	rows = map->rows;
	while (rows)
	{
		i = 0;
		while (i < map->row_size)
		{
			float z = ((t_vertex *)rows->content)[i].vec.z;
			float relative_altitude = ((z - map->z_min) / (map->z_max - map->z_min));
			((t_vertex *)rows->content)[i].color_id = (COLOR_TABLE_SIZE - 1) * relative_altitude;
			i++;
		}
		rows = rows->next;
	}
}

static void	map_make_edges(t_edge **edgesptr, int *size, int map_row_num, int map_row_size)
{
	int	i;
	int	j;
	int	current;
	t_edge *edges;
	
	*size = (map_row_num - 1) * map_row_size + map_row_num * (map_row_size - 1);

	(*edgesptr) = malloc(*size * sizeof(*edges));
	edges = *edgesptr;
	current = 0;
	j = 0;
	while (j < map_row_num)
	{
		i = 0;
		while (i < map_row_size)
		{
			if (i < map_row_size - 1)
			{
				edges[current].start = i + j * map_row_size;
				edges[current].end = (i + 1) + j * map_row_size;
				current++;
			}
			if (j < map_row_num - 1)
			{
				edges[current].start = i + j * map_row_size;
				edges[current].end = i + (j + 1) * map_row_size;
				current++;
			}
			i++;
		}
		j++;
	}
}

int		init_map(t_map *map, const char *filename)
{
	int		fd;
	int		status;

	map->rows = NULL;
	map->row_num = 0;
	map->row_size = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (fail("failed to open map file.\n"));
	status = load_map(fd, map);
	close(fd);
	if (status < 0)
		return (fail("failed to read from file.\n"));
	if (map->row_num == 0)
		return (fail("map empty.\n"));
	map->projected = malloc(map->row_num * map->row_size * sizeof(*map->projected));
	map_assign_colors(map);
	map_make_edges(&map->edges, &map->edges_size, map->row_num, map->row_size);
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
		return (fail("falied to get image data address\n"));
	bitmap->x_dim = x_dim;
	bitmap->y_dim = y_dim;
	return (OK);
}
