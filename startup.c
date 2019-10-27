/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:18:34 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/20 20:57:18 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "mlx.h"
#include "fdf.h"
#include "settings.h"

static void	*fail(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (NULL);
}

t_state		*init_state(void)
{
	t_state	*state;

	if (!(state = (t_state *)malloc(sizeof(*state))))
		return (fail("memory allocation failed.\n"));
	state->stop_program = 0;
	state->animation_pause = START_PAUSED;
	state->animation_step = 0;
	state->redraw = 1;
	state->bench = DO_BENCH;
	state->bench_frames = BENCHMARK_FRAMES;
	state->print_stats = 0;
	state->print_keycodes = 0;
	state->draw_stats = 1;
	state->draw_helpers = 1;
	state->draw_controls = 0;
	state->use_z_buf = 1;
	return (state);
}

void		reset_cam_position(t_things *things)
{
	if (things->map != NULL)
	{
		things->cam->world.x = things->map->row_size / 2;
		things->cam->world.y = things->map->row_num / 2;
		things->cam->world.z = things->map->z_min;
		things->cam->zoom = 0.5 * things->bitmap->x_dim / things->map->row_size;
	}
	else
	{
		things->cam->world = ORIGIN;
		things->cam->zoom = 0.5 * things->bitmap->x_dim;
	}
	things->cam->rot = ORIGIN;
}

t_cam		*init_cam(t_things *things)
{
	t_cam		*cam;

	if (!(cam = (t_cam *)malloc(sizeof(*cam))))
		return (fail("memory allocation failed.\n"));
	cam->z_buf_size = things->bitmap->x_dim * things->bitmap->y_dim;
	cam->z_buf_stride = things->bitmap->x_dim;
	cam->z_buf = (float *)malloc(sizeof(*cam->z_buf) * cam->z_buf_size);
	if (things->map != NULL)
	{
		cam->world.x = things->map->row_size / 2;
		cam->world.y = things->map->row_num / 2;
		cam->world.z = things->map->z_min;
		cam->zoom = 0.5 * things->bitmap->x_dim / things->map->row_size;
		cam->dist = 0.75 * (things->map->row_size + things->map->row_num);
	}
	else
	{
		cam->world = ORIGIN;
		cam->zoom = 0.5 * things->bitmap->x_dim;
		cam->dist = 1;
	}
	cam->z_near = 1;
	cam->z_far = 2 * cam->dist;
	cam->rot = ORIGIN;
	cam->projection = Axonometric;
	cam->altitude_mult = 1;
	return (cam);
}

t_map		*init_map(const char *filename)
{
	int		fd;
	t_map	*g;

	if (!(g = (t_map *)malloc(sizeof(*g))))
		return (fail("memory allocation failed.\n"));
	g->rows = NULL;
	if ((fd = open(filename, O_RDONLY)) > 2)
	{
		if (read_map(fd, g) < 0)
		{
			free(g);
			close(fd);
			return (fail("failed to read from file.\n"));
		}
		if (g->row_num == 0)
		{
			free(g);
			close(fd);
			return (fail("map empty.\n"));
		}
		close(fd);
		map_find_height_range(g);
		map_make_colors(g);
		return (g);
	}
	else
	{
		free(g);
		return (fail("failed to open file.\n"));
	}
}

t_bitmap	*init_bitmap(void *mlx_img_ptr, int x_dim, int y_dim)
{
	t_bitmap	*bitmap;
	int			bpp;
	int			stride;
	int			endianness;

	if (!(bitmap = (t_bitmap *)malloc(sizeof(*bitmap))))
		return (fail("memory allocation failed.\n"));
	bitmap->data = (unsigned int *)mlx_get_data_addr(mlx_img_ptr,
			&bpp, &stride, &endianness);
	bitmap->x_dim = x_dim;
	bitmap->y_dim = y_dim;
	return (bitmap);
}
