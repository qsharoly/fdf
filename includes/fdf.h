/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:00:09 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/17 15:43:32 by qsharoly         ###   ########.fr       */
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

typedef struct	s_grid
{
	t_list		*rows;
	float		z_min;
	float		z_max;
	int			max_row_size;
}				t_grid;

typedef struct	s_my_state
{
	int				stop_program;
	int				frame_advance;
	int				do_step;
	int				redraw;
	int				bench;
	int				bench_frames;
	int				print_stats;
	int				print_keycodes;
	int				draw_stats;
	int				draw_helpers;
	int				draw_controls;
	int				use_z_buf;
	int				keycode;
	enum e_projkind	projection;
}				t_my_state;

typedef struct	s_things
{
	void		*mlx;
	void		*window;
	void		*mlx_image;
	t_bitmap	*bitmap;
	t_my_state	*state;
	t_grid		*grid;
	t_cam		*cam;
}				t_things;

float			ft_fmin(float a, float b);
float			ft_fmax(float a, float b);
t_my_state		*init_state(void);
t_cam			*init_cam(t_things *things);
t_grid			*init_grid(const char *filename);
t_bitmap		*init_bitmap(void *mlx_img_ptr, int x_dim, int y_dim);
void			lst_del_fdf_row(void *row, size_t size);
int				read_grid(int fd, t_list **rows);
void			grid_make_properties(t_grid *mesh);
void			assign_colors_from_z(t_grid *mesh);
void			draw_grid(t_bitmap *bmp, t_cam *cam, t_list *rows);
void			draw_grid_z_buf(t_bitmap *bmp, t_cam *cam, t_list *rows);
void			draw_helpers(t_bitmap *bitmap, t_cam *cam);
void			draw_hud(t_things *my, float frame);
int				draw_controls(void *mlx_ptr, void *mlx_window);
void			ft_put_float_janky(float a);
char			*ft_itoa_float_janky(float a);

#endif
