/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:38:27 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/15 17:35:33 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "libft.h"
#include "math.h"

int		draw_controls(void *mlx_ptr, void *mlx_window)
{
	int		white;
	void	*mp;
	void	*mw;

	mp = mlx_ptr;
	mw = mlx_window;
	white = 0x00FFFFFF;
	mlx_string_put(mp, mw, 20, 50, white, "space = pause/unpause");
	mlx_string_put(mp, mw, 20, 70, white, "    n = next frame");
	mlx_string_put(mp, mw, 20, 90, white, "    s = show stats");
	mlx_string_put(mp, mw, 20, 110, white, "    h = show axis helpers");
	mlx_string_put(mp, mw, 20, 130, white, "    d = print stats");
	mlx_string_put(mp, mw, 20, 150, white, "    a = print keycodes");
	mlx_string_put(mp, mw, 20, 170, white, "    c = hide controls");
	mlx_string_put(mp, mw, 20, 190, white, "    p = switch projection");
	mlx_string_put(mp, mw, 20, 210, white, "  j/k = zoom in/out");
	mlx_string_put(mp, mw, 20, 230, white, "  u/i = altitude multiply +/-");
	mlx_string_put(mp, mw, 20, 250, white, "    q, esc = quit");
	return (0);
}

void	ft_put_float_janky(float a)
{
	ft_putnbr(floor(a));
	ft_putchar('.');
	ft_putnbr(floor((a - floor(a)) * 1000));
}

char	*ft_itoa_float_janky(float a)
{
	char	*s;
	char	*s1;

	s = ft_itoa(floor(a));
	s1 = ft_strjoin(s, ".");
	free(s);
	s = ft_strjoin(s1, ft_itoa(floor((a - floor(a)) * 1000)));
	free(s1);
	return (s);
}

void	draw_hud(t_things *my, float frame)
{
	char		s1[65];
	char		*tmps;

	if (my->state->print_stats == 1)
	{
		ft_putstr("frame ");
		ft_put_float_janky(frame);
		ft_putstr("\n");
	}
	if (my->state->draw_stats == 1)
	{
		s1[0] = '\0';
		ft_strcat(s1, "frame ");
		tmps = ft_itoa_float_janky(frame);
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
