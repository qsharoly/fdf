/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:39:07 by qsharoly          #+#    #+#             */
/*   Updated: 2020/05/24 14:14:16 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include "mlx.h"
#include "libft.h"
#include "fdf.h"
#include "palette.h"
#include "keyboard.h"
#include "settings.h"

void		(*g_cam_setup_func[4])(t_cam *) = {cam_setup_perspective,
	cam_setup_axonometric, cam_setup_military, cam_setup_cavalier};
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
	exit(0);
}

static int	draw_geometry(t_things *my)
{
	struct timeval	t1;
	struct timeval	t2;
	int				dt;
	void			(*draw_func)(t_bitmap, t_cam *, t_vertex, t_vertex);

	fill_rect(my->bitmap, rect(0, 0, my->state.window_width, my->state.window_height), BLACK);
	gettimeofday(&t1, NULL);
	if (my->state.use_zbuf)
		reset_zbuf(&my->cam);
	draw_func = my->state.use_zbuf ? draw_line_gradient_zbuf : draw_line_gradient;
	if (my->map.rows != NULL)
		draw_map(my->bitmap, &my->cam, &my->map, draw_func);
	gettimeofday(&t2, NULL);
	dt = 1000000*(t2.tv_sec - t1.tv_sec) + t2.tv_usec - t1.tv_usec;
	if (my->state.draw_helpers)
		draw_helpers(my->bitmap, &my->cam);
	mlx_put_image_to_window(my->mlx, my->window, my->mlx_image, 0, 0);
	return (dt);
}

static int	the_loop(t_things *my)
{
	static int		frame = 0;
	static double	avg_drawing_time = 0;

	if (my->state.bench && frame > my->state.bench_max_frames)
	{
		printf("Average is %f\n", avg_drawing_time);
		free_things_and_exit(my);
	}
	if (my->state.animation_pause)
	{
		if (my->state.animation_step)
			my->state.animation_step = 0;
		else if (my->state.redraw == 0)
			return (0);
	}
	if (my->state.redraw == 0)
	{
		my->cam.angle.z += 0.05 * M_PI / 100;
		my->cam.angle.x += (-1) * 0.5 * M_PI / 200;
	}
	frame++;
	//g_cam_setup_func[my->cam->projection](my->cam);
	cam_setup_perspective(&my->cam);
	calc_pipeline(&my->cam, my->bitmap);
	avg_drawing_time = (avg_drawing_time * (frame - 1) + draw_geometry(my)) / frame;
	draw_hud(my, frame);
	my->state.redraw = 0;
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
		things->state.animation_pause = 0;
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
	t_things	things;
	char		*caption;
	int			status;

	caption = NULL;
	if (argc > 1)
	{
		things.state = init_state();
		get_options(&things, argc, argv);
		status = init_map(&things.map, argv[argc - 1]);
		if (status == FAIL)
			return (-1);
		ft_putstr_fd("\033[3Dok.\n", 2);
		caption = ft_strjoin("my fdf : ", argv[argc - 1]);
	}
	else
		put_usage_and_exit();
	things.mlx = mlx_init();
	things.window = mlx_new_window(things.mlx, things.state.window_width, things.state.window_height, caption);
	free(caption);
	things.mlx_image = mlx_new_image(things.mlx, things.state.window_width, things.state.window_height);
	init_bitmap(&things.bitmap, things.mlx_image, things.state.window_width, things.state.window_height);
	init_cam(&things.cam, &things);
	mlx_loop_hook(things.mlx, the_loop, &things);
	mlx_key_hook(things.window, key_controls, &things);
	mlx_loop(things.mlx);
	return (0);
}
