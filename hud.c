/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:38:27 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/12 17:05:49 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
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
	mlx_string_put(mp, mw, 20, 130, white, "    d = stats -> stderr");
	mlx_string_put(mp, mw, 20, 150, white, "    c = hide controls");
	mlx_string_put(mp, mw, 20, 170, white, "    p = switch projection");
	mlx_string_put(mp, mw, 20, 190, white, "  j/k = zoom in/out");
	mlx_string_put(mp, mw, 20, 210, white, "  u/i = altitude multiply +/-");
	mlx_string_put(mp, mw, 20, 240, white, "    q, esc = quit");
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
