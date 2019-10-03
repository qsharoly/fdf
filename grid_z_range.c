/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_z_range.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:43:24 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/03 19:00:05 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

/*
** rows contain arrays of t_float3.
** put minimal z value into range.x, maximal z value into range.y
*/

t_float3	grid_z_range(t_list *rows, int row_size)
{
	t_float3	range;
	int			i;
	float		z;

	range.x = 0;
	range.y = 0;
	while (rows)
	{
		i = 0;
		while (i < row_size)
		{
			z = ((t_float3 *)rows->content)[i].z;
			range.x = ft_fmin(z, range.x);
			range.y = ft_fmax(z, range.y);
			i++;
		}
		rows = rows->next;
	}
	range.z = range.y - range.x;
	return (range);
}
