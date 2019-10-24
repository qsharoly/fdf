/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:00:09 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/24 18:57:38 by qsharoly         ###   ########.fr       */
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

# define XDIM 640
# define YDIM 480

typedef struct	s_map
{
	t_list		*rows;
	float		z_min;
	float		z_max;
	int			row_size;
	int			row_num;
}				t_map;

typedef struct	s_state
{
	int				stop_program;
	int				animation_pause;
	int				animation_step;
	int				redraw;
	int				bench;
	int				bench_frames;
	int				print_stats;
	int				print_keycodes;
	int				draw_stats;
	int				draw_helpers;
	int				draw_controls;
	int				use_z_buf;
	enum e_projkind	projection;
}				t_state;

typedef struct	s_things
{
	void		*mlx;
	void		*window;
	void		*mlx_image;
	t_bitmap	*bitmap;
	t_state		*state;
	t_map		*map;
	t_cam		*cam;
}				t_things;

float			ft_fmin(float a, float b);
float			ft_fmax(float a, float b);
void			ft_put_float(float a);
char			*ft_itoa_float(float a);
t_state			*init_state(void);
t_cam			*init_cam(t_things *things);
t_map			*init_map(const char *filename);
t_bitmap		*init_bitmap(void *mlx_img_ptr, int x_dim, int y_dim);
void			lst_del_fdf_row(void *row, size_t size);
int				read_map(int fd, t_map *map);
void			map_find_height_range(t_map *map);
void			map_make_colors(t_map *map);
void			draw_map(t_bitmap *bmp, t_cam *cam, t_map *map, t_list *rows);
void			draw_map_z_buf(t_bitmap *bmp, t_cam *cam, t_map *map,
					t_list *rows);
void			draw_helpers(t_bitmap *bitmap, t_cam *cam);
void			draw_hud(t_things *my, float frame);
int				draw_controls(void *mlx_ptr, void *mlx_window);
void			toggle(int *var);
void			free_things_and_exit(t_things *things);
int				key_controls(int keycode, t_things *param);

#endif
