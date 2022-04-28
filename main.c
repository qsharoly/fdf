/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:39:07 by qsharoly          #+#    #+#             */
/*   Updated: 2022/04/28 05:41:37 by debby            ###   ########.fr       */
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
}

void	free_things_and_exit(t_things *things)
{
	mlx_destroy_window(things->mlx, things->window);
	mlx_destroy_image(things->mlx, things->mlx_image);
	free(things->zbuffer.z);
	free(things->map.edges);
	free(things->map.projected);
	free(things->map.vertices);
	exit(0);
}

static void	bmp_clear(t_bitmap bmp, int color) {
	ft_memset32(bmp.data, color, bmp.x_dim * bmp.y_dim);
}

static void	draw_geometry(t_things *th)
{
	t_line_func	line;

	bmp_clear(th->bitmap, BLACK);
	if (th->state.use_zbuf)
	{
		reset_zbuf(&th->zbuffer);
		line = line_gradient_zbuf;
	}
	else
	{
		line = line_gradient;
	}
	if (th->map.vertices != NULL)
	{
		transform_vertices_v2(th->map.projected, th->map.vertices, th->map.rows * th->map.per_row, &th->cam);
		draw_map(th->bitmap, th->zbuffer, th->map.projected, th->map.edges, th->map.edges_size, line);
	}
	if (th->state.draw_helpers)
		draw_helpers(th->bitmap, &th->cam);
	mlx_put_image_to_window(th->mlx, th->window, th->mlx_image, 0, 0);
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
		microsec = 1000000*(t2.tv_sec - t1.tv_sec) + t2.tv_usec - t1.tv_usec;
		double frames = th->state.frames;
		times->avg_drawing_usec = (times->avg_drawing_usec * (frames - 1) + microsec) / frames;
		times->min_drawing_usec = fmin(microsec, times->min_drawing_usec);
		times->max_drawing_usec = fmax(microsec, times->max_drawing_usec);
		times->total_drawing_seconds += microsec / 1000000;
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
	th.window = mlx_new_window(th.mlx, XDIM, YDIM, "fdf");
	th.mlx_image = mlx_new_image(th.mlx, XDIM, YDIM);
	init_bitmap(&th.bitmap, th.mlx_image, XDIM, YDIM);
	init_color_table(color_table);
	th.bitmap.color_table = color_table;
	init_zbuffer(&th);
	th.cam = init_cam(XDIM, YDIM, &th.map);
	mlx_loop_hook(th.mlx, the_loop, &th);
	mlx_hook(th.window, KeyPress, KeyPressMask, key_press, &th);
	mlx_hook(th.window, KeyRelease, KeyReleaseMask, key_release, &th);
	mlx_hook(th.window, ButtonPress, ButtonPressMask, mouse_press, &th);
	mlx_hook(th.window, ButtonRelease, ButtonReleaseMask, mouse_release, &th);
	mlx_hook(th.window, MotionNotify, PointerMotionMask, mouse_move, &th);
	mlx_loop(th.mlx);
	return (0);
}
