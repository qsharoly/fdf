#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "mlx.h"
#include "fdf.h"
#include "libft.h"

t_float3	project(t_float3 point, t_cam cam, t_bitmap *bmp)
{
	t_float3	proj;
	t_float3	screen;
	float		coeff;

	point = add_float3(point, scalar_mul(cam.world, -1));
	coeff = (cam.dist - dot(point, cam.dir)) / dot(cam.dir, cam.proj_dir);
	proj = add_float3(point, scalar_mul(cam.proj_dir, coeff));

	screen.x = cam.fov * dot(proj, cam.right) + 0.5 * bmp->x_dim;
	screen.y = cam.fov * dot(proj, cam.up) + 0.5 * bmp->y_dim;
	screen.z = dot(proj, cam.dir);
	return (screen);
}

t_float3	normalize(t_float3 point)
{
	return (scalar_mul(point, 1 / length3(point)));
}

t_float2	take_xy(t_float3 point)
{
	t_float2	xy;

	xy.x = point.x;
	xy.y = point.y;
	return (xy);
}

t_float3	rot_x(float angle, t_float3 vec)
{
	t_float3	rot;

	rot.x = vec.x;
	rot.y = cos(angle) * vec.y - sin(angle) * vec.z;
	rot.z = sin(angle) * vec.y + cos(angle) * vec.z;
	return (rot);
}

t_float3	rot_y(float angle, t_float3 vec)
{
	t_float3	rot;

	rot.x = cos(angle) * vec.x - sin(angle) * vec.z;
	rot.y = vec.y;
	rot.z = sin(angle) * vec.x + cos(angle) * vec.z;
	return (rot);
}

t_float3	rot_z(float angle, t_float3 vec)
{
	t_float3	rot;

	rot.x = cos(angle) * vec.x - sin(angle) * vec.y;
	rot.y = sin(angle) * vec.x + cos(angle) * vec.y;
	rot.z = vec.z;
	return (rot);
}

void	draw_edge(t_bitmap *bmp, t_cam cam, t_float3 p1, t_float3 p2, t_rgba color)
{
	t_float3	proj1;
	t_float3	proj2;

	proj1 = project(p1, cam, bmp);
	proj2 = project(p2, cam, bmp);
	draw_line(bmp, take_xy(proj1), take_xy(proj2), color);
}

void	draw_edge_gradient(t_bitmap *bmp, t_cam cam, t_vertex v1, t_vertex v2)
{
	t_float3	proj1;
	t_float3	proj2;

	proj1 = project(v1.vec, cam, bmp);
	proj2 = project(v2.vec, cam, bmp);
	draw_line_gradient(bmp, take_xy(proj1), take_xy(proj2), v1.col, v2.col);
}

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

void	toggle(int *var)
{
	*var = (*var + 1) % 2;
}

#define SPACEBAR 49
#define LETTER_Q 12
#define LETTER_N 45
#define LETTER_S 1
#define LETTER_D 2
#define LETTER_H 4
#define LETTER_C 8
#define LETTER_K 40
#define LETTER_P 35
#define L_SHIFT 257
#define R_SHIFT 258
#define ESC 53

int		key_controls(int keycode, void *param)
{
	t_my_state	*st = (t_my_state *)param;

	ft_putstr_fd("key ", 2);
	ft_putnbr_fd(keycode, 2);
	ft_putstr_fd("\n", 2);
	if (keycode == LETTER_Q || keycode == ESC)
		st->stop_program = 1;
	if (keycode == SPACEBAR)
		toggle(&st->frame_advance);
	if ((keycode == LETTER_N) && (st->frame_advance == 1))
		st->do_step = 1;
	if (keycode == LETTER_D)
		toggle(&st->print_stats);
	if (keycode == LETTER_S)
		toggle(&st->draw_stats);
	if (keycode == LETTER_H)
		toggle(&st->draw_helpers);
	if (keycode == LETTER_C)
		toggle(&st->draw_controls);
	if (keycode == LETTER_P)
		toggle((int *)&st->projection);
	return (0);
}

int		draw_controls(void *mlx_ptr, void *mlx_window)
{
	mlx_string_put(mlx_ptr, mlx_window, 20, 50, 0x00FFFFFF, "space = pause/unpause");
	mlx_string_put(mlx_ptr, mlx_window, 20, 70, 0x00FFFFFF, "    n = next frame");
	mlx_string_put(mlx_ptr, mlx_window, 20, 90, 0x00FFFFFF, "    s = show stats");
	mlx_string_put(mlx_ptr, mlx_window, 20, 110, 0x00FFFFFF, "    h = show helpers");
	mlx_string_put(mlx_ptr, mlx_window, 20, 130, 0x00FFFFFF, "    d = stats -> stderr");
	mlx_string_put(mlx_ptr, mlx_window, 20, 150, 0x00FFFFFF, "    c = show these controls");
	mlx_string_put(mlx_ptr, mlx_window, 20, 170, 0x00FFFFFF, "    p = switch projection");
	mlx_string_put(mlx_ptr, mlx_window, 20, 200, 0x00FFFFFF, "    q, esc = quit");
	return (0);
}

int		the_loop(void *param)
{
	t_things	*my = (t_things *)param;
	struct timespec	frame_start;
	struct timespec frame_end;
	double		fps;
	double		time_taken_msec;
	static float frame;
	char		s1[64] = {};
	static t_rgba		black = {0, 0, 0, 0};
	static t_rgba		white = {255, 255, 255, 0};
	static t_rgba		full_red	= {255, 0, 0, 0};
	static t_rgba		full_green	= {0, 255, 0, 0};
	static t_rgba		full_blue	= {0, 0, 255, 0};
	static t_rgba		mellow1 = {150, 100, 250, 0};
	static t_rgba		mellow2 = {100, 250, 150, 0};
	static t_rgba		mellow3 = {250, 150, 100, 0};
	static t_float3	origin = {0.0, 0.0, 0.0};
	static t_float3	x = {1.0, 0.0, 0.0};
	static t_float3	y = {0.0, 1.0, 0.0};
	static t_float3	z = {0.0, 0.0, 1.0};
	t_float3	dir;
	t_float3	up;
	t_float3	right;
	static t_cam	cam;
	static t_float3	pir[4] = {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0},
		{0.0, 0.5, 0.0}, {0.0, 0.0, 0.5}};

	//camera & projection setup
	dir.x = sin(frame * 0.5 * M_PI / 100);
	dir.y = cos(frame * 0.5 * M_PI / 100);
	dir.z = 0.8;
	dir = normalize(dir);
	right.x = dir.y;
	right.y = -dir.x;
	right.z = 0;
	right = normalize(right);
	up = cross(dir, right);
	if (my->state->projection == Axonometric)
	{
		cam.dist = 1;
		cam.dir = dir;
		cam.up = up;
		cam.right = right;
		cam.proj_dir = cam.dir;
	}
	else if (my->state->projection == Oblique)
	{
		//"Military"
		cam.dist = 1;
		cam.right = add_float3(y, scalar_mul(x, -1));
		cam.right = normalize(cam.right);
		cam.dir = z;
		cam.up = cross(cam.right, cam.dir);
		cam.proj_dir.x = 1 * sin(M_PI / 4);
		cam.proj_dir.y = 1 * cos(M_PI / 4);
		cam.proj_dir.z = 1;
		cam.proj_dir = normalize(cam.proj_dir);
		//"Cavalier"
		/*
		cam.dist = 1;
		cam.right = y;
		cam.dir = scalar_mul(x, -1);
		cam.up = scalar_mul(z, -1);
		cam.proj_dir = rot_z(0.15 * M_PI, cam.dir);
		cam.proj_dir = rot_y(0.15 * M_PI, cam.proj_dir);
		*/
	}
	if (my->mesh != NULL)
	{
		cam.dist = 0;
		cam.world.x = my->mesh->max_row_size / 2;
		cam.world.y = my->mesh->max_row_size / 2;
		cam.world.z = my->mesh->z_min;
		cam.fov = 0.5 * my->bitmap->x_dim / my->mesh->max_row_size;
	}
	else
	{
		cam.dist = 1;
		cam.world.x = 0;
		cam.world.y = 0;
		cam.world.z = 0;
		cam.fov = 0.5 * my->bitmap->x_dim;
	}

	clock_gettime(CLOCK_MONOTONIC, &frame_start);
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
		else
			return (0);
	}
	//physics
	//graphics
	//---black background
	fill_rect(my->bitmap, rect(0, 0, XDIM, YDIM), black);
	//---wire mesh
	if (my->mesh)
		draw_grid(my->bitmap, cam, my->mesh->rows);
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
	clock_gettime(CLOCK_MONOTONIC, &frame_end);
	time_taken_msec = (frame_end.tv_nsec - frame_start.tv_nsec) * 1e-6;
	fps = 1000 / time_taken_msec;
	if (my->state->print_stats == 1)
	{
		dprintf(2, "%7.3lfms, %7.3lffps ", time_taken_msec, fps);
		dprintf(2, "frame %f\n", frame);
	}
	if (my->state->draw_stats == 1)
	{
		snprintf(s1, 63, "%.3lfms %7.3lffps frame %f", time_taken_msec, fps, frame);
		mlx_string_put(my->my_mlx, my->my_window, 10, 10, 0x00FFFFFF, s1);
	}
	if (my->state->draw_controls == 1)
	{
		draw_controls(my->my_mlx, my->my_window);
	}
	frame++;
	return (0);
}

int		main(int argc, char **argv)
{
	t_my_state	state;
	t_things	things;
	t_bitmap	bitmap;
	t_grid		grid;
	int			my_bpp;
	int			my_image_size_line;
	int			my_endianness;
	int			fd;
	char		*caption;

	caption = ft_strdup("my fdf");
	things.mesh = NULL;
	grid.rows = NULL;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		read_grid(fd, &(grid.rows));
		close(fd);
		grid_make_properties(&grid);
		assign_colors_from_z(&grid);
		caption = ft_strjoin(caption, " : ");
		caption = ft_strjoin(caption, argv[1]);
		things.mesh = &grid;
	}
	state.projection = Axonometric;
	state.stop_program = 0;
	state.frame_advance = 0;
	state.do_step = 0;
	state.bench = 1;
	state.bench_frames = 500;
	state.print_stats = 0;
	state.draw_stats = 1;
	state.draw_helpers = 1;
	state.draw_controls = 0;
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
	mlx_loop_hook(things.my_mlx, the_loop, &things);
	mlx_key_hook(things.my_window, key_controls, things.state);
	/*
	mlx_string_put(things.my_mlx, things.my_window, XDIM / 2 - 65, 10, 0x00FFFFDA, "~ m y f d f ~");
	draw_controls(things.my_mlx, things.my_window);
	*/
	mlx_loop(things.my_mlx);
	return (0);
}
