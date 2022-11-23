/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_closedown.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kith <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 03:00:57 by kith              #+#    #+#             */
/*   Updated: 2022/11/23 03:12:23 by kith             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int mlx_closedown(t_xvar *xvar)
{
	int result = XCloseDisplay(xvar->display);
	free(xvar);
	return result;
}
