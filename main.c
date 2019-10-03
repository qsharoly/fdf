#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <signal.h>
#include "mlx.h"
#include "fdf.h"
#include "libft.h"
#define XDIM 640
#define YDIM 480
#define LIMX 1.0
#define LIMY 1.0

typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;
typedef struct	s_uint2
{
	t_uint x;
	t_uint y;
}				t_uint2;
typedef struct	s_uchar3
{
	t_uchar r;
	t_uchar g;
	t_uchar b;
}				t_uchar3;
typedef struct	s_rgba
{
	t_uchar r;
	t_uchar g;
	t_uchar b;
	t_uchar a;
}				t_rgba;

typedef struct	s_bitmap
{
	unsigned int	*data;
	t_uint	x_dim;
	t_uint	y_dim;
}				t_bitmap;

typedef struct	s_my_state
{
	int	stop_program;
	int	frame_advance;
	int	do_step;
	int bench;
	t_uint	bench_frames;
	int	print_stats;
	int	draw_stats;
	int draw_helpers;
	int	draw_controls;
	int keycode;
}				t_my_state;

typedef struct	s_cam
{
	t_float3	world;
	t_float3	dir;
	t_float3	up;
	t_float3	right;
	t_float3	proj_dir;
	float		dist;
	float		fov;
}				t_cam;

typedef struct	s_grid
{
	t_list		*rows;
	int			row_size;
	float		z_range;
	float		z_min;
	float		z_max;
}				t_grid;

typedef struct	s_things
{
	void		*my_mlx;
	void		*my_window;
	void		*mlx_image;
	t_bitmap	*bitmap;
	t_my_state	*state;
	t_grid		*mesh;
}				t_things;

unsigned int	rgba_to_int(t_rgba color)
{
	unsigned int	out = 0;

	out += color.r << 16;
	out += color.g << 8;
	out += color.b << 0;
	return (out);
}

t_rgba	get_pixel(t_bitmap *bmp, t_uint x, t_uint y)
{
	unsigned int		color;
	t_rgba	out;

	color = *(bmp->data + x + y * bmp->x_dim);
	out.r = *((char *)&color + 2);
	out.g = *((char *)&color + 1);
	out.b = *((char *)&color + 0);
	out.a = 0;

	return (out);
}

void	set_pixel(t_bitmap *bmp, t_uint x, t_uint y, t_rgba color)
{
	*(bmp->data + x + y * bmp->x_dim) = rgba_to_int(color);
}

t_bitmap	*bitmap_init(t_bitmap *bmp, t_uint x_dim, t_uint y_dim)
{
	bmp->data = malloc(x_dim * y_dim * sizeof(t_rgba));
	bmp->x_dim = x_dim;
	bmp->y_dim = y_dim;
	return (bmp);
}

float	squared(float a)
{
	return (a * a);
}

float	distance(t_float2 a, t_float2 b)
{
	return (sqrt(squared(a.x - b.x) + squared(a.y - b.y)));
}

/*
** gradient: interpolate between colors
** mix is expected to be in range [0.0, 1.0]
*/

t_rgba	gradient(t_rgba col1, t_rgba col2, float mix)
{
	t_rgba	color;

	color.r = sqrt(squared(col1.r) * mix + squared(col2.r) * (1 - mix));
	color.g = sqrt(squared(col1.g) * mix + squared(col2.g) * (1 - mix));
	color.b = sqrt(squared(col1.b) * mix + squared(col2.b) * (1 - mix));
	return (color);
}

t_rgba	bad_gradient(t_rgba col1, t_rgba col2, float mix)
{
	t_rgba	bad;

	bad.r = col1.r * mix + col2.r * (1 - mix);
	bad.g = col1.g * mix + col2.g * (1 - mix);
	bad.b = col1.b * mix + col2.b * (1 - mix);
	return (bad);
}

void	do_blend(t_bitmap *bmp, t_float2 p, t_rgba color)
{
	float	pixel_size = sqrt((LIMX * LIMX / (bmp->x_dim * bmp->x_dim))
			+ (LIMY * LIMY / (bmp->y_dim * bmp->y_dim)));
	t_uint	x_index;
	t_uint	y_index;
	t_uint	floor_x;
	t_uint	floor_y;
	t_uint	i;
	t_uint	j;
	t_float2	pixel_geom;
	float	ratio;
	float	dist;

	floor_x = floor((p.x / LIMX) * (float)bmp->x_dim);
	floor_y = floor((p.y / LIMY) * (float)bmp->y_dim);
	j = 0;
	while (j < 2)
	{
		if ((floor_y + j) >= bmp->y_dim)
			break ;
		i = 0;
		while (i < 2)
		{
			if ((floor_x + i) >= bmp->x_dim)
				break ;
			x_index = floor_x + i;
			y_index = floor_y + j;
			pixel_geom.x = LIMX * (float)x_index / (float)bmp->x_dim;
			pixel_geom.y = LIMY * (float)y_index / (float)bmp->y_dim;
			dist = distance(pixel_geom, p);
			if (dist > pixel_size)
				ratio = 0;
			else
			{
				ratio = (pixel_size - dist) / pixel_size;
				ratio = ratio * ratio;
			}
			set_pixel(bmp, x_index, y_index,
					gradient(color, get_pixel(bmp, x_index, y_index), ratio));
			i++;
		}
		j++;
	}
}

void	draw_line(t_bitmap *bmp, t_float2 a, t_float2 b, t_rgba color)
{
	t_float2	pixel_size = {LIMX / bmp->x_dim, LIMY / bmp->y_dim};
	t_float2	zero = {0.0, 0.0};
	float		pixel_diameter = distance(zero, pixel_size);
	float		length = distance(a, b);
	t_float2	p;
	float		dt = 0.5 * pixel_diameter / length;
	float		t;

	t = 0;
	while (t < 1)
	{
		p.x = a.x + t * (b.x - a.x);
		p.y = a.y + t * (b.y - a.y);
		t += dt;
		do_blend(bmp, p, color);
	}
}

void	draw_line_gradient(t_bitmap *bmp, t_float2 a, t_float2 b, t_rgba a_color, t_rgba b_color)
{
	t_float2	pixel_size = {LIMX / bmp->x_dim, LIMY / bmp->y_dim};
	t_float2	zero = {0.0, 0.0};
	float		pixel_diameter = distance(zero, pixel_size);
	float		length = distance(a, b);
	t_float2	p;
	float		dt = 0.5 * pixel_diameter / length;
	float		t;

	t = 0;
	while (t < 1)
	{
		p.x = a.x + t * (b.x - a.x);
		p.y = a.y + t * (b.y - a.y);
		do_blend(bmp, p, gradient(a_color, b_color, 1 - t));
		t += dt;
	}
}

void	fill_rect(t_bitmap *bmp, t_uint x, t_uint y, t_uint width, t_uint height, t_rgba color)
{
	t_uint i;
	t_uint j;

	j = 0;
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			set_pixel(bmp, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

int		near_eq(float a, float b)
{
	float	eps = 1e-8;
	if (fabs(a - b) < eps)
		return (1);
	else
		return (0);
}

t_float2	add_float2(t_float2 a, t_float2 b)
{
	t_float2	sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	return (sum);
}

t_float3	sub_float3(t_float3 a, t_float3 b)
{
	t_float3	d;

	d.x = a.x - b.x;
	d.y = a.y - b.y;
	d.z = a.z - b.z;
	return (d);
}

t_float3	add_float3(t_float3 a, t_float3 b)
{
	t_float3	sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	sum.z = a.z + b.z;
	return (sum);
}

float		dot(t_float3 a, t_float3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_float3	cross(t_float3 a, t_float3 b)
{
	t_float3	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

t_float3	scalar_mul(t_float3 vec, float s)
{
	vec.x *= s;
	vec.y *= s;
	vec.z *= s;
	return (vec);
}

float	length3(t_float3 vec)
{
	return (sqrt(dot(vec, vec)));
}

t_float2	project(t_float3 point, t_cam cam)
{
	t_float3	proj;
	t_float2	screen;
	float		coeff;

	point = sub_float3(point, cam.world);
	coeff = (cam.dist - dot(point, cam.dir)) / dot(cam.dir, cam.proj_dir);
	proj = add_float3(point, scalar_mul(cam.proj_dir, coeff));

	screen.x = cam.fov * dot(proj, cam.right) + 0.5 * LIMX;
	screen.y = cam.fov * dot(proj, cam.up) + 0.5 * LIMY;
	return (screen);
}

void	draw_edge(t_bitmap *bmp, t_cam cam, t_float3 v1, t_float3 v2, t_rgba color)
{
	t_float2	proj1;
	t_float2	proj2;

	proj1 = project(v1, cam);
	proj2 = project(v2, cam);
	draw_line(bmp, proj1, proj2, color);
}

void	draw_edge_gradient(t_bitmap *bmp, t_cam cam, t_float3 v1, t_float3 v2, t_rgba col1, t_rgba col2)
{
	t_float2	proj1;
	t_float2	proj2;

	proj1 = project(v1, cam);
	proj2 = project(v2, cam);
	draw_line_gradient(bmp, proj1, proj2, col1, col2);
}

t_rgba	color_from_z(t_float3 vertex, float z_min, float z_max)
{
	t_rgba		high = {150, 100, 250, 0};
	t_rgba		low = {100, 250, 150, 0};
	t_rgba		inferno = {250, 150, 100, 0};

	if (z_max - z_min  == 0.0)
		return (low);
	else
		if (vertex.z >= 0.0)
			return (gradient(low, high, (z_max - vertex.z) / z_max));
		else
			return (gradient(low, inferno, (vertex.z - z_min) / -z_min));
}

void	draw_grid(t_bitmap *bmp, t_cam cam, t_grid *mesh)
{
	int			i;
	int			j;
	t_rgba		color1;
	t_rgba		color2;
	t_float3	vertex1;
	t_float3	vertex2;
	t_list		*row;

	j = 0;
	row = mesh->rows;
	while (row)
	{
		i = 0;
		while (i < mesh->row_size)
		{
			vertex1 = ((t_float3 *)row->content)[i];
			color1 = color_from_z(vertex1, mesh->z_min, mesh->z_max);
			if (row->next)
			{
				vertex2 = ((t_float3 *)row->next->content)[i];
				color2 = color_from_z(vertex2, mesh->z_min, mesh->z_max);
				draw_edge_gradient(bmp, cam, vertex1, vertex2, color1, color2);
			}
			if (i < mesh->row_size - 1)
			{
				vertex2 = ((t_float3 *)row->content)[i + 1];
				color2 = color_from_z(vertex2, mesh->z_min, mesh->z_max);
				draw_edge_gradient(bmp, cam, vertex1, vertex2, color1, color2);
			}
			i++;
		}
		row = row->next;
		j++;
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
#define LETTER_K 40
#define L_SHIFT 257
#define R_SHIFT 258

int		key_controls(int keycode, void *param)
{
	t_my_state	*st = (t_my_state *)param;

	//dprintf(2, "key %d\n", keycode);
	if (keycode == LETTER_Q)
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
	if (keycode == LETTER_K)
		toggle(&st->draw_controls);
	return (0);
}

int		draw_controls(void *mlx_ptr, void *mlx_window)
{
	mlx_string_put(mlx_ptr, mlx_window, 20, 50, 0x00FFFFFF, "space = pause/unpause");
	mlx_string_put(mlx_ptr, mlx_window, 20, 70, 0x00FFFFFF, "    n = next frame");
	mlx_string_put(mlx_ptr, mlx_window, 20, 90, 0x00FFFFFF, "    s = show stats");
	mlx_string_put(mlx_ptr, mlx_window, 20, 110, 0x00FFFFFF, "    h = show helpers");
	mlx_string_put(mlx_ptr, mlx_window, 20, 130, 0x00FFFFFF, "    d = stats -> stderr");
	mlx_string_put(mlx_ptr, mlx_window, 20, 150, 0x00FFFFFF, "    k = show these controls");
	mlx_string_put(mlx_ptr, mlx_window, 20, 180, 0x00FFFFFF, "    q = quit");
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
	t_rgba		black = {0, 0, 0, 0};
	t_rgba		white = {255, 255, 255, 0};
	t_rgba		full_red	= {255, 0, 0, 0};
	t_rgba		full_green	= {0, 255, 0, 0};
	t_rgba		full_blue	= {0, 0, 255, 0};
	t_rgba		mellow1 = {150, 100, 250, 0};
	t_rgba		mellow2 = {100, 250, 150, 0};
	t_rgba		mellow3 = {250, 150, 100, 0};
	t_float3	origin = {0.0, 0.0, 0.0};
	t_float3	x = {1.0, 0.0, 0.0};
	t_float3	y = {0.0, 1.0, 0.0};
	t_float3	z = {0.0, 0.0, 1.0};
	t_float3	dir;
	t_float3	up;
	t_float3	right;
	static t_cam	cam;
	static t_float3	pir[4] = {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0},
		{0.0, 0.5, 0.0}, {0.0, 0.0, 0.5}};

	dir.x = sin(frame * 0.5 * M_PI / 100);
	dir.y = cos(frame * 0.5 * M_PI / 100);
	dir.z = 0.5;
	dir = scalar_mul(dir, 1 / length3(dir));
	right.x = dir.y;
	right.y = -dir.x;
	right.z = 0;
	right = scalar_mul(right, 1 / length3(right));
	up = cross(dir, right);
	up = scalar_mul(up, 1 / length3(up));
	cam.dir = dir;
	cam.up = up;
	cam.right = right;
	cam.proj_dir = cam.dir;
	//cam.world - position that is going to be projected to the center of screen
	cam.world.x = my->mesh->row_size / 2;
	cam.world.y = my->mesh->row_size / 2;
	cam.world.z = 0;
	//cam.dist doesnt influence parallel projections
	cam.dist = 1;
	//cam.fov right now is just a screen space scale multiplier
	cam.fov = LIMX / my->mesh->row_size;

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
	fill_rect(my->bitmap, 0, 0, XDIM, YDIM, black);
	//---wire mesh
	draw_grid(my->bitmap, cam, my->mesh);
	if (my->state->draw_helpers)
	{
		//---pyramid
		draw_edge(my->bitmap, cam, pir[0], pir[1], white);
		draw_edge(my->bitmap, cam, pir[0], pir[2], white);
		draw_edge(my->bitmap, cam, pir[0], pir[3], white);
		draw_edge(my->bitmap, cam, pir[1], pir[2], mellow1);
		draw_edge(my->bitmap, cam, pir[1], pir[3], mellow2);
		draw_edge(my->bitmap, cam, pir[2], pir[3], mellow3);
		//---axes;
		draw_edge(my->bitmap, cam, origin, x, full_blue);
		draw_edge(my->bitmap, cam, origin, y, full_green);
		draw_edge(my->bitmap, cam, origin, z, full_red);
		//---cam world position
		draw_edge(my->bitmap, cam, cam.world, add_float3(x, cam.world), mellow1);
		draw_edge(my->bitmap, cam, cam.world, add_float3(y, cam.world), mellow2);
		draw_edge(my->bitmap, cam, cam.world, add_float3(z, cam.world), mellow3);
	}
	//"draw_call"
	mlx_put_image_to_window(my->my_mlx, my->my_window, my->mlx_image, 0, 0);
	//stats
	clock_gettime(CLOCK_MONOTONIC, &frame_end);
	time_taken_msec = (frame_end.tv_nsec - frame_start.tv_nsec) * 1e-6;
	fps = 1000 / time_taken_msec;
#if	1
	if (my->state->print_stats == 1)
	{
		dprintf(2, "%7.3lfms, %7.3lffps ", time_taken_msec, fps);
		dprintf(2, "frame %f\n", frame);
	}
	if (my->state->draw_stats == 1)
	{
		snprintf(s1, 63, "%.3lfms %7.3lffps frame %f", time_taken_msec, fps, frame);
		mlx_string_put(my->my_mlx, my->my_window, 10, 10, rgba_to_int(white), s1);
	}
	if (my->state->draw_controls == 1)
	{
		draw_controls(my->my_mlx, my->my_window);
	}
#endif
	frame++;
	return (0);
}

int		main(int argc, char **argv)
{
	t_my_state	state;
	t_things	things;
	t_bitmap	bitmap;
	t_grid		mesh;
	int			my_bpp;
	int			my_image_size_line;
	int			my_endianness;
	int			fd;
	t_float3	z_props;

	mesh.rows = NULL;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		mesh.row_size = read_grid(fd, &mesh.rows);
		close(fd);
		z_props = grid_z_range(mesh.rows, mesh.row_size);
		mesh.z_range = z_props.z;
		mesh.z_min = z_props.x;
		mesh.z_max = z_props.y;
	}
	things.mesh = &mesh;
	state.stop_program = 0;
	state.frame_advance = 0;
	state.do_step = 0;
	state.bench = 0;
	state.bench_frames = 500;
	state.print_stats = 0;
	state.draw_stats = 1;
	state.draw_helpers = 0;
	state.draw_controls = 0;
	things.my_mlx = mlx_init();
	things.my_window = mlx_new_window(things.my_mlx, XDIM, YDIM, ft_strjoin("pulsr : ", argv[1]));
	things.mlx_image = mlx_new_image(things.my_mlx, XDIM, YDIM);
	bitmap.data = (unsigned int *)mlx_get_data_addr(things.mlx_image, &my_bpp, &my_image_size_line, &my_endianness);
	bitmap.x_dim = XDIM;
	bitmap.y_dim = YDIM;
	things.bitmap = &bitmap;
	things.state = &state;
	mlx_loop_hook(things.my_mlx, the_loop, &things);
	mlx_key_hook(things.my_window, key_controls, things.state);
	mlx_string_put(things.my_mlx, things.my_window, XDIM / 2 - 65, 10, 0x00FFFFDA, "~ p u l s r ~");
	draw_controls(things.my_mlx, things.my_window);
	mlx_loop(things.my_mlx);
	return (0);
}
