/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:38:27 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/24 18:03:45 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "libft.h"
#include "fdf.h"
#include "palette.h"

void	draw_helpers(t_bitmap *bitmap, t_cam *cam)
{
	t_view			view;

	view.bmp = bitmap;
	view.cam = cam;
	draw_edge(view, cam->world, add_float3(XUNIT, cam->world),
			PEACH);
	draw_edge(view, cam->world, add_float3(YUNIT, cam->world),
			LIGHTGREEN);
	draw_edge(view, cam->world, add_float3(ZUNIT, cam->world),
			PURPLE);
	draw_edge(view, ORIGIN, XUNIT, RED);
	draw_edge(view, ORIGIN, YUNIT, GREEN);
	draw_edge(view, ORIGIN, ZUNIT, BLUE);
}

int		draw_controls(void *mlx_ptr, void *mlx_window)
{
	int		white;
	void	*mp;
	void	*mw;
	int		v;

	mp = mlx_ptr;
	mw = mlx_window;
	white = 0x00ffffff;
	v = 50;
	mlx_string_put(mp, mw, 20, v, white, "space = pause/unpause animation");
	mlx_string_put(mp, mw, 20, v += 20, white, "    n = next frame if paused");
	mlx_string_put(mp, mw, 20, v += 20, white, "    s = show fps");
	mlx_string_put(mp, mw, 20, v += 20, white, "    h = show axis helpers");
	mlx_string_put(mp, mw, 20, v += 20, white, "    d = print stats");
	mlx_string_put(mp, mw, 20, v += 20, white, "    a = print keycodes");
	mlx_string_put(mp, mw, 20, v += 20, white, "    c = show controls");
	mlx_string_put(mp, mw, 20, v += 20, white, "    p = switch projection");
	mlx_string_put(mp, mw, 20, v += 20, white, "  j/k = zoom in/out");
	mlx_string_put(mp, mw, 20, v += 20, white, "  u/i = altitude adjust +/-");
	mlx_string_put(mp, mw, 20, v += 20, white, "    q, esc = quit");
	return (0);
}

void	ft_put_float(float a)
{
	ft_putnbr(floor(a));
	ft_putchar('.');
	ft_putnbr(floor((a - floor(a)) * 1000));
}

char	*ft_itoa_float(float a)
{
	char	*s;
	char	*s1;
	char	*s2;

	s = ft_itoa(floor(a));
	s1 = ft_strjoin(s, ".");
	free(s);
	s = ft_itoa(floor((a - floor(a)) * 1000));
	s2 = ft_strjoin(s1, s);
	free(s);
	free(s1);
	return (s2);
}

void	draw_hud(t_things *my, float frame)
{
	char		s1[65];
	char		*tmps;

	if (my->state->print_stats == 1)
	{
		ft_putstr("frame ");
		ft_put_float(frame);
		ft_putstr("\n");
	}
	if (my->state->draw_stats == 1)
	{
		s1[0] = '\0';
		ft_strcat(s1, "frame ");
		tmps = ft_itoa_float(frame);
		ft_strcat(s1, tmps);
		free(tmps);
		ft_strcat(s1, "zoom = ");
		tmps = ft_itoa_float(my->cam->zoom);
		ft_strcat(s1, tmps);
		free(tmps);
		if (my->state->use_z_buf)
			ft_strcat(s1, " z_buf on");
		else
			ft_strcat(s1, " z_buf off");
		mlx_string_put(my->mlx, my->window, 10, 10, 0x00FFFFFF, s1);
	}
	if (my->state->draw_controls == 1)
		draw_controls(my->mlx, my->window);
}
