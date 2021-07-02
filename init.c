/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:18:34 by qsharoly          #+#    #+#             */
/*   Updated: 2021/07/02 04:49:23 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "mlx.h"
#include "fdf.h"
#include "settings.h"

int			fail(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (FAIL);
}

t_state		init_state(void)
{
	t_state	state;

	state.window_width = XDIM;
	state.window_height = YDIM;
	state.bench_max_frames = BENCHMARK_FRAMES;
	state.stop_program = 0;
	state.animation_pause = 1;
	state.animation_step = 0;
	state.redraw = 1;
	state.bench = 0;
	state.print_keycodes = 0;
	state.draw_stats = 1;
	state.draw_helpers = 1;
	state.draw_controls = 0;
	state.use_zbuf = 1;
	return (state);
}

int		init_cam(t_cam *cam, t_things *things)
{
	cam->zbuf_size = things->bitmap.x_dim * things->bitmap.y_dim;
	cam->zbuf_stride = things->bitmap.x_dim;
	cam->zbuf = malloc(sizeof(*cam->zbuf) * cam->zbuf_size);
	if (!cam->zbuf)
		return (fail("failed to malloc z-buffer\n"));
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
	cam->projection = Perspective;
	cam->altitude_scale = 1;
	return (GOOD);
}

int		init_map(t_map *map, const char *filename)
{
	int		fd;
	int		status;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (fail("failed to open file.\n"));
	map->rows = NULL;
	status = load_map(fd, map);
	close(fd);
	if (status < 0)
		return (fail("failed to read from file.\n"));
	if (map->row_num == 0)
		return (fail("map empty.\n"));
	map_find_height_range(map);
	map_make_colors(map);
	return (GOOD);
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
	return (GOOD);
}
