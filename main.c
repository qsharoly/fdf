/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:39:07 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/27 18:58:30 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "fdf.h"
#include "palette.h"
#include "keyboard.h"

void		(*g_cam_setup_func[4])(t_cam *) = {cam_setup_perspective,
	cam_setup_axonometric, cam_setup_military, cam_setup_cavalier};
const char	*g_projnames[4] = {"Perspective", "Isometric", "Military",
	"Cavalier"};

static void	put_usage_and_exit(void)
{
	ft_putstr("Usage: fdf <filename>\n"
			"When running, press c to view controls.\n");
	exit(0);
}

void		free_things_and_exit(t_things *things)
{
	mlx_destroy_window(things->mlx, things->window);
	mlx_destroy_image(things->mlx, things->mlx_image);
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
		my->cam->rot.z += 0.05 * M_PI / 100;
		my->cam->rot.x += (-1) * 0.5 * M_PI / 200;
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
		ft_putstr_fd("\033[3Dok.\n", 2);
		caption = ft_strjoin("my fdf : ", argv[1]);
	}
	else
		put_usage_and_exit();
	ft_putstr_fd("try mlx_init()\n", 2);
	things.mlx = mlx_init();
	ft_putstr_fd("try mlx_new_window()\n", 2);
	things.window = mlx_new_window(things.mlx, XDIM, YDIM, caption);
	free(caption);
	ft_putstr_fd("try mlx_new_image()\n", 2);
	things.mlx_image = mlx_new_image(things.mlx, XDIM, YDIM);
	things.bitmap = init_bitmap(things.mlx_image, XDIM, YDIM);
	things.cam = init_cam(&things);
	things.state = init_state();
	ft_putstr_fd("try mlx_loop_hook()\n", 2);
	mlx_loop_hook(things.mlx, the_loop, &things);
	ft_putstr_fd("try mlx_key_hook()\n", 2);
	mlx_key_hook(things.window, key_controls, &things);
	ft_putstr_fd("try mlx_loop()\n", 2);
	mlx_loop(things.mlx);
	return (0);
}
