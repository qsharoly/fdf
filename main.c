/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:39:07 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/27 17:54:12 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "fdf.h"
#include "palette.h"
#include "keyboard.h"

static void	put_usage_and_exit(void)
{
	ft_putstr("usage: fdf <filename>\n press c to view controls\n");
	exit(0);
}

void		free_things_and_exit(t_things *things)
{
	mlx_destroy_window(things->mlx, things->window);
	mlx_destroy_image(things->mlx, things->mlx_image);
	free(things->bitmap);
	free(things->state);
	free(things->cam);
	if (things->map)
	{
		ft_lstdel(&things->map->rows, lst_del_fdf_row);
		free(things->map);
	}
	exit(0);
}

static void	draw_geometry(t_things *my)
{
	fill_rect(my->bitmap, rect(0, 0, XDIM, YDIM), BLACK);
	if (my->map)
	{
		if (my->state->use_z_buf)
		{
			reset_z_buf(my->cam);
			draw_map_z_buf(my->bitmap, my->cam, my->map, my->map->rows);
		}
		else
			draw_map(my->bitmap, my->cam, my->map, my->map->rows);
	}
	if (my->state->draw_helpers)
		draw_helpers(my->bitmap, my->cam);
	mlx_put_image_to_window(my->mlx, my->window, my->mlx_image, 0, 0);
}

/*
** For clockwise rotation we need to increment angle in negative direction
*/

static int	the_loop(t_things *my)
{
	static int	frame;

	if (my->state->bench == 1 && frame > my->state->bench_frames)
		free_things_and_exit(my);
	if (my->state->animation_pause == 1)
	{
		if (my->state->animation_step == 1)
			my->state->animation_step = 0;
		else if (my->state->redraw == 0)
			return (0);
	}
	if (my->state->redraw == 0)
	{
		my->cam->rot.z += (-1) * 0.05 * M_PI / 100;
		my->cam->rot.x += (-1) * 0.5 * M_PI / 100;
		frame++;
	}
	g_cam_setup_func[my->cam->projection](my->cam);
	draw_geometry(my);
	draw_hud(my, frame);
	my->state->redraw = 0;
	return (0);
}

int			main(int argc, char **argv)
{
	t_things	things;
	char		*caption;

	caption = NULL;
	things.map = NULL;
	if (argc == 2)
	{
		if ((things.map = init_map(argv[1])) == NULL)
			return (-1);
		ft_putstr_fd("\033[3D ok.\n", 2);
		caption = ft_strjoin("my fdf : ", argv[1]);
	}
	else
		put_usage_and_exit();
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
