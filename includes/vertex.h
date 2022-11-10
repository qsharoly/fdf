/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kith <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 00:53:36 by kith              #+#    #+#             */
/*   Updated: 2022/11/07 08:12:53 by kith             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEX_H
# define VERTEX_H

# include "vector.h"

typedef struct	s_vertex
{
	union {
		struct {
			float	x;
			float	y;
			float	z;
		};
		t_vec3 vec;
	};
	float altitude;
}				t_vertex;

typedef struct	s_edge
{
	unsigned int start;
	unsigned int end;
}				t_edge;

#endif
