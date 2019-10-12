/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:00:09 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/12 17:32:37 by qsharoly         ###   ########.fr       */
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
	int				draw_stats;
	int				draw_helpers;
	int				draw_controls;
	int				keycode;
	enum e_projkind	projection;
}				t_my_state;

typedef struct	s_things
{
	void		*my_mlx;
	void		*my_window;
	void		*mlx_image;
	t_bitmap	*bitmap;
	t_my_state	*state;
	t_grid		*grid;
	t_cam		*cam;
}				t_things;

float			ft_fmin(float a, float b);
float			ft_fmax(float a, float b);
int				read_grid(int fd, t_list **rows);
void			grid_make_properties(t_grid *mesh);
void			assign_colors_from_z(t_grid *mesh);
int				draw_controls(void *mlx_ptr, void *mlx_window);
void			ft_put_float_janky(float a);
char			*ft_itoa_float_janky(float a);

#endif
