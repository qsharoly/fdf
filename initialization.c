/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:18:34 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/20 17:01:56 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "mlx.h"
#include "fdf.h"
#include "benchmark.h"

t_my_state	*init_state(void)
{
	t_my_state	*state;

	if (!(state = (t_my_state *)malloc(sizeof(*state))))
		return (NULL);
	state->projection = Axonometric;
	state->stop_program = 0;
	state->frame_advance = 1;
	state->do_step = 0;
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

t_cam		*init_cam(t_things *things)
{
	t_cam		*cam;

	if (!(cam = (t_cam *)malloc(sizeof(*cam))))
		return (NULL);
	cam->z_buf_size = things->bitmap->x_dim * things->bitmap->y_dim;
	cam->z_buf = (float *)malloc(sizeof(*cam->z_buf) * cam->z_buf_size);
	cam->altitude_mult = 1;
	if (things->grid != NULL)
	{
		cam->dist = 0;
		cam->world.x = things->grid->max_row_size / 2;
		cam->world.y = things->grid->max_row_size / 2;
		cam->world.z = things->grid->z_min;
		cam->fov = 0.5 * things->bitmap->x_dim / things->grid->max_row_size;
	}
	else
	{
		cam->dist = 1;
		cam->world.x = 0;
		cam->world.y = 0;
		cam->world.z = 0;
		cam->fov = 0.5 * things->bitmap->x_dim;
	}
	return (cam);
}

t_grid		*init_grid(const char *filename)
{
	int		fd;
	t_grid	*g;

	if (!(g = (t_grid *)malloc(sizeof(*g))))
		return (NULL);
	g->rows = NULL;
	if ((fd = open(filename, O_RDONLY)) > 2)
	{
		if (read_grid(fd, &g->rows) < 0)
		{
			ft_putstr_fd("failed to read from file.\n", 2);
			free(g);
			close(fd);
			return (NULL);
		}
		close(fd);
		grid_make_properties(g);
		assign_colors_from_z(g);
		return (g);
	}
	else
	{
		ft_putstr_fd("falied to open file.\n", 2);
		free(g);
		return (NULL);
	}
}

t_bitmap	*init_bitmap(void *mlx_img_ptr, int x_dim, int y_dim)
{
	t_bitmap	*bitmap;
	int			bpp;
	int			stride;
	int			endianness;

	if (!(bitmap = (t_bitmap *)malloc(sizeof(*bitmap))))
		return (NULL);
	bitmap->data = (unsigned int *)mlx_get_data_addr(mlx_img_ptr,
			&bpp, &stride, &endianness);
	bitmap->x_dim = x_dim;
	bitmap->y_dim = y_dim;
	return (bitmap);
}
