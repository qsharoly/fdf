/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:39:07 by qsharoly          #+#    #+#             */
/*   Updated: 2021/07/04 02:12:10 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include "mlx.h"
#include "mlx_int.h"
#include "libft.h"
#include "fdf.h"
#include "palette.h"
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

void		free_things_and_exit(t_things *things)
{
	mlx_destroy_window(things->mlx, things->window);
	mlx_destroy_image(things->mlx, things->mlx_image);
	free(things->cam.zbuf);
	free(things->map.projected);
	ft_lstclear(&things->map.rows, del_map_row);
	exit(0);
}

static void	bmp_clear(t_bitmap bmp, int color) {
	ft_memset32(bmp.data, color, bmp.x_dim * bmp.y_dim);
}

static int	draw_geometry(t_things *th)
{
	struct timeval	t1;
	struct timeval	t2;
	int				dt;
	void			(*draw_func)(t_bitmap, t_cam *, t_vertex, t_vertex);

	bmp_clear(th->bitmap, BLACK);
	gettimeofday(&t1, NULL);
	if (th->state.use_zbuf) {
		reset_zbuf(&th->cam);
		draw_func = line_dda_gradient_zbuf;
	}
	else {
		draw_func = draw_line_gradient;
	}
	if (th->map.rows != NULL)
	{
		apply_transform(th->map.projected, &th->map, &th->cam);
		draw_map(th->bitmap, &th->cam, &th->map, draw_func);
	}
	gettimeofday(&t2, NULL);
	dt = 1000000*(t2.tv_sec - t1.tv_sec) + t2.tv_usec - t1.tv_usec;
	if (th->state.draw_helpers)
		draw_helpers(th->bitmap, &th->cam);
	mlx_put_image_to_window(th->mlx, th->window, th->mlx_image, 0, 0);
	return (dt);
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
	static int		frame = 0;
	static double	avg_drawing_time = 0;
	int				usec;

	if (th->state.bench && frame > th->state.bench_max_frames)
	{
		printf("Average is %f\n", avg_drawing_time);
		free_things_and_exit(th);
	}
	if (th->state.animation_running)
		th->state.animation_step = 1;
	if (th->state.animation_step)
	{
		th->cam.angle.z -= 0.05 * M_PI / 100;
		th->cam.angle.x -= 0.5 * M_PI / 200;
		th->state.animation_step = 0;
		th->state.redraw = 1;
	}
	if (th->state.redraw)
	{
		frame++;
		calc_camera_transform(&th->cam);
		usec = draw_geometry(th);
		avg_drawing_time = (avg_drawing_time * (frame - 1) + usec) / frame;
		draw_hud(th, usec);
	}
	th->state.redraw = 0;
	return (0);
}

/*
** if option -b is specified, run in benchmark mode
*/

static void		get_options(t_things *things, int argc, char **argv)
{
	int		arg;
	int		i;

	arg = 1;
	if (ft_strcmp(argv[arg], "-b") == 0)
	{
		things->state.bench = 1;
		things->state.animation_running = 1;
		if (argc > arg + 1 && (i = ft_atoi(argv[arg + 1])) > 0)
		{
			things->state.bench_max_frames = i;
			arg++;
		}
		arg++;
	}
}

int			main(int argc, char **argv)
{
	t_things	th;
	int			outcome;

	if (argc > 1)
	{
		th.state = init_state();
		get_options(&th, argc, argv);
		outcome = init_map(&th.map, argv[argc - 1]);
		if (outcome == FAIL)
			return (-1);
		ft_putstr_fd("\033[3Dok.\n", 2);
	}
	else
		put_usage_and_exit();
	th.mlx = mlx_init();
	th.window = mlx_new_window(th.mlx, XDIM, YDIM, "fdf");
	th.mlx_image = mlx_new_image(th.mlx, XDIM, YDIM);
	init_bitmap(&th.bitmap, th.mlx_image, XDIM, YDIM);
	init_cam(&th.cam, &th);
	mlx_loop_hook(th.mlx, the_loop, &th);
	mlx_hook(th.window, KeyPress, KeyPressMask, key_press, &th);
	mlx_hook(th.window, KeyRelease, KeyReleaseMask, key_release, &th);
	mlx_hook(th.window, ButtonPress, ButtonPressMask, mouse_press, &th);
	mlx_hook(th.window, ButtonRelease, ButtonReleaseMask, mouse_release, &th);
	mlx_hook(th.window, MotionNotify, PointerMotionMask, mouse_move, &th);
	mlx_loop(th.mlx);
	return (0);
}
