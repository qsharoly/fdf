/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:00:09 by qsharoly          #+#    #+#             */
/*   Updated: 2024/09/03 01:33:30 by kith             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "vector.h"
# include "camera.h"
# include "draw.h"
# include "color.h"

# define OK 1
# define FAIL 0

# define TOGGLE(var) ((var) = (!(var)))

# define MINIDTOA_BUF_SIZE (ITOA_BUF_SIZE * 2 + 3) // sign + dot + '\0'

typedef struct	s_map
{
	t_vertex	*projected;
	t_vertex	*vertices;
	float		z_min;
	float		z_max;
	int			rows;
	int			per_row;
	t_edge		*edges;
	int			edges_count;
	int 		color_table[COLOR_TABLE_SIZE];
}				t_map;

typedef struct	s_time_stats
{
	double	drawing_avg_usec;
	double	drawing_min_usec;
	double	drawing_max_usec;
	double	drawing_total_seconds;
	double	*all;
	int		count;
}				t_time_stats;

typedef struct	s_state
{
	int				frame_count;
	int				bench_max_frames;
	unsigned int	shift_is_down:1;
	unsigned int	ctrl_is_down:1;
	unsigned int	lmb_is_down:1;
	int				mousex;
	int				mousey;
	unsigned int	stop_program:1;
	unsigned int	animation_running:1;
	unsigned int	animation_step:1;
	unsigned int	redraw:1;
	unsigned int	bench:1;
	unsigned int	print_keycodes:1;
	unsigned int	draw_stats:1;
	unsigned int	draw_helpers:1;
	unsigned int	draw_controls:1;
	unsigned int	use_zbuf:1;
}				t_state;

typedef struct	s_things
{
	void		*mlx;
	void		*window;
	void		*mlx_image;
	t_state		state;
	t_time_stats	time_stats;
	t_bitmap	bitmap;
	t_zbuffer	zbuffer;
	t_map		map;
	t_cam		cam;
}				t_things;

void			log_failure(const char *msg);
char			*ft_mini_dtoa(char *buffer, int size, float a);
t_state			init_state(void);
t_cam			init_cam(int window_x_dim, int window_y_dim, const t_map *map);
int				init_map(t_map *map, const char *filename);
int				init_bitmap(t_bitmap *bitmap, const void *mlx_img_ptr, int x_dim, int y_dim);
int				init_zbuffer(t_zbuffer *zb, int x_dim, int y_dim);
int 			load_map_v2(const char *filename, t_map *map);
void			map_find_height_range(t_map *map);
void			map_make_colors(t_map *map);
void			transform_vertices(t_vertex *result, const t_vertex *vertices,
					int vertices_size, const t_cam *cam, int x_dim, int y_dim);
void			draw_edges(t_bitmap bmp, const t_vertex *verts,
					const t_edge *edges, int edges_size);
void			draw_edges_zbuf(t_bitmap bmp, t_zbuffer zb, const t_vertex *verts,
					const t_edge *edges, int edges_size);
void			draw_helpers(t_bitmap bitmap, t_cam *cam);
void			draw_hud(t_things *my, float frame);
int				draw_controls(void *mlx_ptr, void *mlx_window);
void			reset_cam(t_cam *cam, const t_map *map);
void			print_stats(int frame_count, t_time_stats st);
void			free_things_and_exit(t_things *th);
int				hook_key_press(int keycode, t_things *th);
int				hook_key_release(int keycode, t_things *th);
int				hook_mouse_move(int x, int y, t_things *th);
int				hook_mouse_press(int button, int x, int y, t_things *th);
int				hook_mouse_release(int button, int x, int y, t_things *th);

#endif
