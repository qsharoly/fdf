/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:06:18 by qsharoly          #+#    #+#             */
/*   Updated: 2021/07/03 01:08:47 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEX_H
# define VERTEX_H

# include "vector.h"

typedef struct	s_vertex
{
	t_vec3		vec;
	int			color;
}				t_vertex;

#endif
