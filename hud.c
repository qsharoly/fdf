/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:38:27 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/27 16:40:59 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "libft.h"
#include "fdf.h"
#include "palette.h"

extern const char	*g_projnames[4];

int			draw_controls(void *mlx_ptr, void *mlx_window)
{
	int		white;
	void	*mp;
	void	*mw;
	int		v;

	mp = mlx_ptr;
	mw = mlx_window;
	white = 0x00ffffff;
	v = 30;
	mlx_string_put(mp, mw, 20, v += 20, white, "yhuo = rotate cam");
	mlx_string_put(mp, mw, 20, v += 20, white, "ijkl = translate cam");
	mlx_string_put(mp, mw, 20, v += 20, white, "  ,. = zoom in/out");
	mlx_string_put(mp, mw, 20, v += 20, white, "  tg = altitude adjust +/-");
	mlx_string_put(mp, mw, 20, v += 20, white, "   p = switch projection");
	mlx_string_put(mp, mw, 20, v += 20, white, "   r = reset cam");
	mlx_string_put(mp, mw, 20, v += 20, white, "   z = show stats");
	mlx_string_put(mp, mw, 20, v += 20, white, "   x = show axis");
	mlx_string_put(mp, mw, 20, v += 20, white, "   a = print keycodes");
	mlx_string_put(mp, mw, 20, v += 20, white, "   c = show controls");
	mlx_string_put(mp, mw, 20, v += 20, white, "    b = toggle z buffer");
	mlx_string_put(mp, mw, 20, v += 20, white, "space = (un)pause animation");
	mlx_string_put(mp, mw, 20, v += 20, white, "    n = next frame if paused");
	mlx_string_put(mp, mw, 20, v += 20, white, "q, esc = quit");
	return (0);
}

void		draw_edge(t_view view, t_vec3 a, t_vec3 b, t_rgba color)
{
	t_vec2	aa;
	t_vec2	bb;

	aa = take_xy(project(a, view.cam, view.bmp));
	bb = take_xy(project(b, view.cam, view.bmp));
	draw_line(view.bmp, aa, bb, color);
}

void		draw_helpers(t_bitmap bitmap, t_cam *cam)
{
	t_view			view;

	view.bmp = bitmap;
	view.cam = cam;
	draw_edge(view, cam->world, add_vec3(XUNIT, cam->world),
			PEACH);
	draw_edge(view, cam->world, add_vec3(YUNIT, cam->world),
			LIGHTGREEN);
	draw_edge(view, cam->world, add_vec3(ZUNIT, cam->world),
			PURPLE);
	draw_edge(view, ORIGIN, XUNIT, RED);
	draw_edge(view, ORIGIN, YUNIT, GREEN);
	draw_edge(view, ORIGIN, ZUNIT, BLUE);
}

static void	ft_append(char *tgt, char *varname, float varval)
{
	char *valstr;

	ft_strcat(tgt, varname);
	valstr = ft_itoa_float(varval);
	ft_strcat(tgt, valstr);
	free(valstr);
}

void		draw_hud(t_things *my, float frame)
{
	char		s1[120];

	if (my->state.draw_stats == 1)
	{
		s1[0] = '\0';
		ft_append(s1, "frame ", frame);
		ft_append(s1, ", zoom = ", my->cam.zoom);
		if (my->state.use_zbuf)
			ft_strcat(s1, ", z_buf on");
		else
			ft_strcat(s1, ", z_buf off");
		ft_strcat(s1, ", projection = ");
		ft_strcat(s1, g_projnames[my->cam.projection]);
		mlx_string_put(my->mlx, my->window, 10, 10, 0x00FFFFFF, s1);
	}
	if (my->state.draw_controls == 1)
		draw_controls(my->mlx, my->window);
}
