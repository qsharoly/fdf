/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:38:27 by qsharoly          #+#    #+#             */
/*   Updated: 2022/04/12 14:07:29 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "libft.h"
#include "fdf.h"
#include "color.h"

extern const char	*g_projnames[4];

int			draw_controls(void *mlx_ptr, void *mlx_window)
{
	void	*mp;
	void	*mw;
	int		v;

	mp = mlx_ptr;
	mw = mlx_window;
	v = 30;
	mlx_string_put(mp, mw, 20, v += 20, WHITE, "yhuo = rotate cam");
	mlx_string_put(mp, mw, 20, v += 20, WHITE, "ijkl = translate cam");
	mlx_string_put(mp, mw, 20, v += 20, WHITE, "  ,. = zoom in/out");
	mlx_string_put(mp, mw, 20, v += 20, WHITE, "  tg = altitude adjust +/-");
	mlx_string_put(mp, mw, 20, v += 20, WHITE, "   p = switch projection");
	mlx_string_put(mp, mw, 20, v += 20, WHITE, "   r = reset cam");
	mlx_string_put(mp, mw, 20, v += 20, WHITE, "   z = show stats");
	mlx_string_put(mp, mw, 20, v += 20, WHITE, "   x = show axis");
	mlx_string_put(mp, mw, 20, v += 20, WHITE, "   a = print keycodes");
	mlx_string_put(mp, mw, 20, v += 20, WHITE, "   c = show controls");
	mlx_string_put(mp, mw, 20, v += 20, WHITE, "    b = toggle z buffer");
	mlx_string_put(mp, mw, 20, v += 20, WHITE, "space = (un)pause animation");
	mlx_string_put(mp, mw, 20, v += 20, WHITE, "    n = next frame if paused");
	mlx_string_put(mp, mw, 20, v += 20, WHITE, "q, esc = quit");
	return (0);
}

static void		draw_edge(t_view view, t_vec3 a, t_vec3 b, int color)
{
	a = geom_to_pixel(a, view.cam);
	b = geom_to_pixel(b, view.cam);
	line_solid(view.bmp, a, b, color);
}

void		draw_helpers(t_bitmap bitmap, t_cam *cam)
{
	t_view			view;

	view.bmp = bitmap;
	view.cam = cam;
	draw_edge(view, cam->target, add3(XUNIT, cam->target), RED);
	draw_edge(view, cam->target, add3(YUNIT, cam->target), GREEN);
	draw_edge(view, cam->target, add3(ZUNIT, cam->target), BLUE);
	draw_edge(view, ORIGIN, XUNIT, RED);
	draw_edge(view, ORIGIN, YUNIT, GREEN);
	draw_edge(view, ORIGIN, ZUNIT, BLUE);
}

static void	ft_append(char *tgt, char *description, float value)
{
	char *tmp;

	ft_strcat(tgt, description);
	tmp = ft_mini_dtoa(value);
	ft_strcat(tgt, tmp);
	free(tmp);
}

float	rad2deg(float radians)
{
	return (radians * 180 / M_PI);
}

void		draw_hud(t_things *th, float usec)
{
	char		s1[120];

	if (th->state.draw_stats == 1)
	{
		s1[0] = '\0';
		ft_append(s1, "", usec);
		ft_append(s1, "us , zoom = ", th->cam.zoom);
		ft_append(s1, ", cam.angle[x = ", rad2deg(th->cam.angle.x));
		ft_append(s1, ", y = ", rad2deg(th->cam.angle.y));
		ft_append(s1, ", z = ", rad2deg(th->cam.angle.z));
		if (th->state.use_zbuf)
			ft_strcat(s1, "], z_buf on");
		else
			ft_strcat(s1, ", z_buf off");
		ft_strcat(s1, ", projection = ");
		ft_strcat(s1, g_projnames[th->cam.projection]);
		mlx_string_put(th->mlx, th->window, 10, 10, WHITE, s1);
	}
	if (th->state.draw_controls == 1)
		draw_controls(th->mlx, th->window);
}
