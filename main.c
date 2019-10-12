#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "fdf.h"
#include "libft.h"
#include "keyboard.h"

void	draw_grid(t_bitmap *bmp, t_cam cam, t_list *rows)
{
	int			i;
	t_vertex	vertex1;
	t_vertex	vertex2;

	while (rows)
	{
		i = 0;
		while (i < (int)(rows->content_size / sizeof(t_vertex)))
		{
			vertex1 = ((t_vertex *)rows->content)[i];
			if (i < (int)(rows->content_size / sizeof(t_vertex)) - 1)
			{
				vertex2 = ((t_vertex *)rows->content)[i + 1];
				draw_edge_gradient(bmp, cam, vertex1, vertex2);
			}
			if (rows->next)
			{
				vertex2 = ((t_vertex *)rows->next->content)[i];
				draw_edge_gradient(bmp, cam, vertex1, vertex2);
			}
			i++;
		}
		rows = rows->next;
	}
}

int		the_loop(void *param)
{
	t_things	*my = (t_things *)param;
	static float frame;
	char		s1[64] = {};
	char		*tmps;
	int			white_i = 0x00FFFFFF;
	static t_rgba	black = {0, 0, 0, 0};
	static t_rgba	white = {255, 255, 255, 0};
	static t_rgba	full_red	= {255, 0, 0, 0};
	static t_rgba	full_green	= {0, 255, 0, 0};
	static t_rgba	full_blue	= {0, 0, 255, 0};
	static t_rgba	mellow1 = {150, 100, 250, 0};
	static t_rgba	mellow2 = {100, 250, 150, 0};
	static t_rgba	mellow3 = {250, 150, 100, 0};
	static t_float3	origin = {0.0, 0.0, 0.0};
	static t_float3	x = {1.0, 0.0, 0.0};
	static t_float3	y = {0.0, 1.0, 0.0};
	static t_float3	z = {0.0, 0.0, 1.0};
	static t_cam	cam;
	static t_float3	pir[4] = {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0},
		{0.0, 0.5, 0.0}, {0.0, 0.0, 0.5}};
	static float	cam_rotation;

	cam = *(my->cam);
	//inputs
	if ((my->state->stop_program == 1)
			|| ((my->state->bench == 1) && (frame > my->state->bench_frames)))
	{
		mlx_destroy_window(my->my_mlx, my->my_window);
		free(my->bitmap->data);
		exit(0);
	}
	if (my->state->frame_advance == 1)
	{
		if (my->state->do_step == 1)
			my->state->do_step = 0;
		else if (my->state->redraw == 0)
			return (0);
	}
	//physics
	if (my->state->redraw == 0)
	{
		frame++;
		cam_rotation = frame * 0.5 * M_PI / 100;
	}
	//camera & projection setup
	if (my->state->projection == Axonometric)
	{
		cam.dir.x = sin(cam_rotation);
		cam.dir.y = cos(cam_rotation);
		cam.dir.z = 0.8;
		cam.dir = normalize(cam.dir);
		cam.right.x = cam.dir.y;
		cam.right.y = -cam.dir.x;
		cam.right.z = 0;
		cam.right = normalize(cam.right);
		cam.up = cross(cam.dir, cam.right);
		cam.proj_dir = cam.dir;
	}
	else if (my->state->projection == Oblique_Military)
	{
		cam.right = add_float3(x, scalar_mul(y, -1));
		cam.right = normalize(cam.right);
		cam.dir = z;
		cam.up = cross(cam.dir, cam.right);
		cam.proj_dir.x = 1 * sin(M_PI / 4);
		cam.proj_dir.y = 1 * cos(M_PI / 4);
		cam.proj_dir.z = 1;
		cam.proj_dir = normalize(cam.proj_dir);
	}
	else if (my->state->projection == Oblique_Cavalier)
	{
		cam.right = x;
		cam.dir = scalar_mul(y, -1);
		cam.up = scalar_mul(z, -1);
		cam.proj_dir = rot_z(- 0.15 * M_PI, cam.dir);
		cam.proj_dir = rot_x(0.15 * M_PI, cam.proj_dir);
	}
	//graphics
	fill_rect(my->bitmap, rect(0, 0, XDIM, YDIM), black);
	if (my->grid)
		draw_grid(my->bitmap, cam, my->grid->rows);
	if (my->state->draw_helpers)
	{
		//---cam world position
		draw_edge(my->bitmap, cam, cam.world, add_float3(x, cam.world), mellow1);
		draw_edge(my->bitmap, cam, cam.world, add_float3(y, cam.world), mellow2);
		draw_edge(my->bitmap, cam, cam.world, add_float3(z, cam.world), mellow3);
		//---axes;
		draw_edge(my->bitmap, cam, origin, x, full_blue);
		draw_edge(my->bitmap, cam, origin, y, full_green);
		draw_edge(my->bitmap, cam, origin, z, full_red);
		//---pyramid
		draw_edge(my->bitmap, cam, pir[0], pir[1], white);
		draw_edge(my->bitmap, cam, pir[0], pir[2], white);
		draw_edge(my->bitmap, cam, pir[0], pir[3], white);
		draw_edge(my->bitmap, cam, pir[1], pir[2], mellow1);
		draw_edge(my->bitmap, cam, pir[1], pir[3], mellow2);
		draw_edge(my->bitmap, cam, pir[2], pir[3], mellow3);
	}
	//"draw_call"
	mlx_put_image_to_window(my->my_mlx, my->my_window, my->mlx_image, 0, 0);
	//stats
	if (my->state->print_stats == 1)
	{
		ft_putstr("frame ");
		ft_put_float_janky(frame);
		ft_putstr("\n");
	}
	if (my->state->draw_stats == 1)
	{
		s1[0] = '\0';
		ft_strcat(s1, "frame ");
		tmps = ft_itoa_float_janky(frame);
		ft_strcat(s1, tmps);
		free(tmps);
		mlx_string_put(my->my_mlx, my->my_window, 10, 10, white_i, s1);
	}
	if (my->state->draw_controls == 1)
	{
		draw_controls(my->my_mlx, my->my_window);
	}
	if (my->state->redraw)
		my->state->redraw = 0;
	return (0);
}

void	init_state(t_things *things)
{
	things->state->projection = Axonometric;
	things->state->stop_program = 0;
	things->state->frame_advance = 0;
	things->state->do_step = 0;
	things->state->redraw = 0;
	things->state->bench = 0;
	things->state->bench_frames = 500;
	things->state->print_stats = 0;
	things->state->draw_stats = 1;
	things->state->draw_helpers = 1;
	things->state->draw_controls = 0;
}

void	init_cam(t_things *things)
{
	t_cam	*cam;

	cam = things->cam;
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
}

int		init_grid(t_things *things, char *filename)
{
	int		fd;

	things->grid = malloc(sizeof(t_grid));
	things->grid->rows = NULL;
	fd = open(filename, O_RDONLY);
	read_grid(fd, &things->grid->rows);
	close(fd);
	grid_make_properties(things->grid);
	assign_colors_from_z(things->grid);
	return (1);
}

int		main(int argc, char **argv)
{
	t_things	things;
	t_bitmap	bitmap;
	t_my_state	state;
	t_cam		cam;
	int			my_bpp;
	int			my_image_size_line;
	int			my_endianness;
	char		*caption;

	if (argc == 2)
	{
		caption = ft_strjoin("my fdf : ", argv[1]);
		init_grid(&things, argv[1]);
	}
	else
	{
		caption = ft_strdup("my fdf");
		things.grid = NULL;
	}
	things.my_mlx = mlx_init();
	things.my_window = mlx_new_window(things.my_mlx, XDIM, YDIM, caption);
	free(caption);
	things.mlx_image = mlx_new_image(things.my_mlx, XDIM, YDIM);
	bitmap.data = (unsigned int *)mlx_get_data_addr(things.mlx_image,
									&my_bpp, &my_image_size_line, &my_endianness);
	bitmap.x_dim = XDIM;
	bitmap.y_dim = YDIM;
	things.bitmap = &bitmap;
	things.state = &state;
	things.cam = &cam;
	init_state(&things);
	init_cam(&things);
	mlx_loop_hook(things.my_mlx, the_loop, &things);
	mlx_key_hook(things.my_window, key_controls, &things);
	mlx_loop(things.my_mlx);
	return (0);
}
