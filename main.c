/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:39:07 by qsharoly          #+#    #+#             */
/*   Updated: 2024/02/23 11:04:27 by kith             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include "mlx.h"
#include "mlx_int.h"
#include "libft.h"
#include "fdf.h"
#include "color.h"
#include "keyboard.h"
#include "mouse.h"
#include "settings.h"

const char	*g_projnames[4] = {"Perspective", "Isometric", "Military",
	"Cavalier"};

static void	put_usage_and_exit(void)
{
	ft_putstr("Usage: fdf FILE\n"
			"When running, press c to view controls.\n");
	exit(0);
}

void	print_time_stats(int frames, t_time_stats times)
{
	printf(" Frames: %d\n", frames);
	printf(" Total drawing: %fsec\n", times.total_drawing_seconds);
	printf(" Min: %8.1fus ", times.min_drawing_usec);
	printf(" Avg: %8.1fus\n", times.avg_drawing_usec);
	printf(" Max: %8.1fus\n", times.max_drawing_usec);
	int print_all = 0;
	if (print_all) {
		printf(" All:\n");
		for (int i = 0; i < times.count; ++i) {
			printf("%.2f, ", times.all[i]);
		}
	}
}

void	free_things_and_exit(t_things *things)
{
	mlx_destroy_window(things->mlx, things->window);
	mlx_destroy_image(things->mlx, things->mlx_image);
	mlx_closedown(things->mlx);
	free(things->state.time_stats.all);
	free(things->zbuffer.z);
	free(things->map.edges);
	free(things->map.projected);
	free(things->map.vertices);
	exit(0);
}

static void	draw_geometry(t_things *th)
{
	ft_bzero32(th->bitmap.data, th->bitmap.x_dim * th->bitmap.y_dim);
	transform_vertices(th->map.projected, th->map.vertices, th->map.rows * th->map.per_row, &th->cam, th->bitmap.x_dim, th->bitmap.y_dim);
	if (th->state.use_zbuf)
	{
		ft_memset32f(th->zbuffer.z, -INFINITY, th->zbuffer.size);
		draw_edges_zbuf(th->bitmap, th->zbuffer, th->map.projected, th->map.edges,
				th->map.edges_size);
	}
	else
	{
		draw_edges(th->bitmap, th->map.projected, th->map.edges, th->map.edges_size);
	}
	if (th->state.draw_helpers)
		draw_helpers(th->bitmap, &th->cam);
}

/*
** animation step can be caused by
**	- 'animation_running' == 1
**	- a dedicated keypress
** redraw can be caused by
**	- animation step
**	- any keypress that requires redraw
**	- initial render when starting program
*/

static int	the_loop(t_things *th)
{
	struct timeval	t1;
	struct timeval	t2;
	t_time_stats	*times = &th->state.time_stats;
	double			microsec;

	if (th->state.bench && th->state.frames >= th->state.bench_max_frames)
	{
		print_time_stats(th->state.frames, th->state.time_stats);
		free_things_and_exit(th);
	}
	if (th->state.animation_running)
		th->state.animation_step = 1;
	if (th->state.animation_step)
	{
		th->cam.angle.z -= 0.001 * M_PI;
		th->cam.angle.x += 0.005 * M_PI;
		th->cam.zoom += 0.005;
		th->state.animation_step = 0;
		th->state.redraw = 1;
	}
	if (th->state.redraw)
	{
		th->state.frames++;
		gettimeofday(&t1, NULL);
		calc_camera_transform(&th->cam);
		draw_geometry(th);
		gettimeofday(&t2, NULL);
		mlx_put_image_to_window(th->mlx, th->window, th->mlx_image, 0, 0);
		microsec = 1000000*(t2.tv_sec - t1.tv_sec) + t2.tv_usec - t1.tv_usec;
		double frames = th->state.frames;
		times->avg_drawing_usec = (times->avg_drawing_usec * (frames - 1) + microsec) / frames;
		times->min_drawing_usec = fmin(microsec, times->min_drawing_usec);
		times->max_drawing_usec = fmax(microsec, times->max_drawing_usec);
		times->total_drawing_seconds += microsec / 1000000;
		times->all[times->count++] = microsec;
		draw_hud(th, microsec);
	}
	th->state.redraw = 0;
	return (0);
}

/*
** if option -b is specified, run in benchmark mode
*/

static void		get_options(t_state *state, int argc, char **argv)
{
	int		i;
	int		n;

	i = 1;
	if (ft_strcmp(argv[i], "-b") == 0)
	{
		state->bench = 1;
		state->animation_running = 1;
		if (argc > i + 1 && (n = ft_atoi(argv[i + 1])) > 0)
		{
			state->bench_max_frames = n;
			i++;
		}
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_things	th;
	int			ok;
	int			color_table[COLOR_TABLE_SIZE];

	if (argc <= 1)
		put_usage_and_exit();
	th.state = init_state();
	get_options(&th.state, argc, argv);
	ok = init_map(&th.map, argv[argc - 1]);
	if (!ok)
		return (-1);
	th.mlx = mlx_init();
	if (!th.mlx) {
		ft_putstr_fd("mlx_init failed!\n", 2);
		return -1;
	}

	th.window = mlx_new_window(th.mlx, XDIM, YDIM, "fdf");
	th.mlx_image = mlx_new_image(th.mlx, XDIM, YDIM);
	init_bitmap(&th.bitmap, th.mlx_image, XDIM, YDIM);
	init_zbuffer(&th.zbuffer, XDIM, YDIM);
	init_color_table(color_table);
	th.bitmap.color_table = color_table;
	th.cam = init_cam(XDIM, YDIM, &th.map);
	th.state.time_stats.all = malloc(th.state.bench_max_frames* sizeof(*th.state.time_stats.all));
	mlx_loop_hook(th.mlx, the_loop, &th);
	mlx_hook(th.window, KeyPress, KeyPressMask, hook_key_press, &th);
	mlx_hook(th.window, KeyRelease, KeyReleaseMask, hook_key_release, &th);
	mlx_hook(th.window, ButtonPress, ButtonPressMask, hook_mouse_press, &th);
	mlx_hook(th.window, ButtonRelease, ButtonReleaseMask, hook_mouse_release, &th);
	mlx_hook(th.window, MotionNotify, PointerMotionMask, hook_mouse_move, &th);
	mlx_loop(th.mlx);
	return (0);
}
