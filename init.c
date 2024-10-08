/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:18:34 by qsharoly          #+#    #+#             */
/*   Updated: 2024/09/03 01:53:11 by kith             ###   ########.fr       */
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
		.shift_is_down = 0,
		.ctrl_is_down = 0,
		.lmb_is_down = 0,
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
	};
	return (state);
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

int		init_bitmap(t_bitmap *bitmap, const void *mlx_img_ptr, int x_dim, int y_dim)
{
	int			bpp;
	int			stride;
	int			endianness;

	bitmap->data = (int *)mlx_get_data_addr((void *)mlx_img_ptr,
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

int		init_zbuffer(t_zbuffer *zb, int x_dim, int y_dim)
{
	zb->size = x_dim * y_dim;
	zb->stride = x_dim;
	zb->z = malloc(sizeof(zb->z[0]) * zb->size);
	if (!zb->z)
	{
		log_failure("failed to malloc z-buffer\n");
		return (FAIL);
	}
	return (OK);
}
