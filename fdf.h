/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:00:09 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/03 18:59:51 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"

typedef struct	s_float2
{
	float	x;
	float	y;
}				t_float2;

typedef struct	s_float3
{
	float	x;
	float	y;
	float	z;
}				t_float3;

float			ft_fmax(float a, float b);
float			ft_fmin(float a, float b);
int				read_grid(int fd, t_list **rows);
t_float3		grid_z_range(t_list *rows, int row_size);

#endif
