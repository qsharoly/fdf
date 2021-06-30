/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:00:09 by qsharoly          #+#    #+#             */
/*   Updated: 2021/06/30 20:35:32 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "bitmap.h"
# include "vector.h"
# include "vertex.h"
# include "projection.h"
# include "draw.h"

# define GOOD 1
# define FAIL 0

# define TOGGLE(var) ((var) = (!(var)))

typedef struct	s_map
{
	t_list		*rows;
	float		z_min;
	float		z_max;
	int			row_size;
	int			row_num;
}				t_map;

typedef struct	s_edge
{
	t_vertex	v1;
	t_vertex	v2;
}				t_edge;

typedef struct	s_state
{
	int				bench_max_frames;
	unsigned int	dragging;
	int				mousex;
	int				mousey;
	unsigned int	stop_program:1;
	unsigned int	animation_pause:1;
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
	t_bitmap	bitmap;
	t_state		state;
	t_map		map;
	t_cam		cam;
}				t_things;

int				fail(char *msg);
float			ft_fmin(float a, float b);
float			ft_fmax(float a, float b);
char			*ft_mini_dtoa(float a);
t_state			init_state(void);
int				init_cam(t_cam *cam, t_things *th);
int				init_map(t_map *map, const char *filename);
int				init_bitmap(t_bitmap *bitmap, const void *mlx_img_ptr, int x_dim, int y_dim);
void			lst_del_fdf_row(void *row, size_t size);
int				load_map(int fd, t_map *map);
void			map_find_height_range(t_map *map);
void			map_make_colors(t_map *map);
void			draw_map(t_bitmap bmp, t_cam *cam, const t_map *map,
				void (*draw_line)(t_bitmap, t_cam *, t_vertex, t_vertex));
void			reset_cam(t_things *things);
void			draw_helpers(t_bitmap bitmap, t_cam *cam);
void			draw_hud(t_things *my, float frame);
int				draw_controls(void *mlx_ptr, void *mlx_window);
void			free_things_and_exit(t_things *th);
int				key_press(int keycode, t_things *th);
int				key_release(int keycode, t_things *th);
int				mouse_move(int x, int y, t_things *th);
int				mouse_press(int button, int x, int y, t_things *th);
int				mouse_release(int button, int x, int y, t_things *th);

#endif
