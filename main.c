/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:39:07 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/15 18:03:29 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "fdf.h"
#include "palette.h"
#include "libft.h"
#include "keyboard.h"

static void	draw_helpers(t_bitmap *bitmap, t_cam *cam)
{
	static t_float3	pir[4] = {ORIGIN, {0.5, 0.0, 0.0},
		{0.0, 0.5, 0.0}, {0.0, 0.0, 0.5}};

	draw_edge(bitmap, cam, cam->world, add_float3(XUNIT, cam->world),
			RGBA_PURPLISH);
	draw_edge(bitmap, cam, cam->world, add_float3(YUNIT, cam->world),
			RGBA_LIGHTGREEN);
	draw_edge(bitmap, cam, cam->world, add_float3(ZUNIT, cam->world),
			RGBA_PEACH);
	draw_edge(bitmap, cam, ORIGIN, XUNIT, RGBA_BLUE);
	draw_edge(bitmap, cam, ORIGIN, YUNIT, RGBA_GREEN);
	draw_edge(bitmap, cam, ORIGIN, ZUNIT, RGBA_RED);
	draw_edge(bitmap, cam, pir[0], pir[1], RGBA_WHITE);
	draw_edge(bitmap, cam, pir[0], pir[2], RGBA_WHITE);
	draw_edge(bitmap, cam, pir[0], pir[3], RGBA_WHITE);
	draw_edge(bitmap, cam, pir[1], pir[2], RGBA_PURPLISH);
	draw_edge(bitmap, cam, pir[1], pir[3], RGBA_LIGHTGREEN);
	draw_edge(bitmap, cam, pir[2], pir[3], RGBA_PEACH);
}

static void	free_things_and_exit(t_things *things)
{
	mlx_destroy_window(things->mlx, things->window);
	mlx_destroy_image(things->mlx, things->mlx_image);
	free(things->bitmap);
	free(things->state);
	free(things->cam);
	if (things->grid)
	{
		ft_lstdel(&things->grid->rows, lst_del_fdf_row);
		free(things->grid);
	}
	exit(0);
}

static int	the_loop(void *param)
{
	t_things		*my;
	static float	frame;
	static t_rgba	black = {0, 0, 0, 0};
	static float	cam_rotation;

	my = (t_things *)param;
	if ((my->state->stop_program == 1)
			|| ((my->state->bench == 1) && (frame > my->state->bench_frames)))
		free_things_and_exit(my);
	if (my->state->frame_advance == 1)
	{
		if (my->state->do_step == 1)
			my->state->do_step = 0;
		else if (my->state->redraw == 0)
			return (0);
	}
	if (my->state->redraw == 0)
	{
		frame++;
		cam_rotation = frame * 0.5 * M_PI / 100;
	}
	if (my->state->projection == Axonometric)
		cam_setup_axonometric(my->cam, cam_rotation);
	else if (my->state->projection == Oblique_Military)
		cam_setup_military(my->cam);
	else if (my->state->projection == Oblique_Cavalier)
		cam_setup_cavalier(my->cam);
	fill_rect(my->bitmap, rect(0, 0, XDIM, YDIM), black);
	if (my->grid)
	{
		if (my->state->use_z_buf)
		{
			reset_z_buf(my->cam);
			draw_grid_z_buf(my->bitmap, my->cam, my->grid->rows);
		}
		else
			draw_grid(my->bitmap, my->cam, my->grid->rows);
	}
	if (my->state->draw_helpers)
		draw_helpers(my->bitmap, my->cam);
	mlx_put_image_to_window(my->mlx, my->window, my->mlx_image, 0, 0);
	draw_hud(my, frame);
	if (my->state->redraw)
		my->state->redraw = 0;
	return (0);
}

int			main(int argc, char **argv)
{
	t_things	things;
	char		*caption;

	if (argc == 2)
	{
		caption = ft_strjoin("my fdf : ", argv[1]);
		things.grid = init_grid(argv[1]);
	}
	else
	{
		caption = ft_strdup("my fdf");
		things.grid = NULL;
	}
	things.mlx = mlx_init();
	things.window = mlx_new_window(things.mlx, XDIM, YDIM, caption);
	free(caption);
	things.mlx_image = mlx_new_image(things.mlx, XDIM, YDIM);
	things.bitmap = init_bitmap(things.mlx_image, XDIM, YDIM);
	things.cam = init_cam(&things);
	things.state = init_state();
	mlx_loop_hook(things.mlx, the_loop, &things);
	mlx_key_hook(things.window, key_controls, &things);
	mlx_loop(things.mlx);
	return (0);
}
