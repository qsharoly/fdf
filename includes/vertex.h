/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kith <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 00:53:36 by kith              #+#    #+#             */
/*   Updated: 2023/02/06 08:58:30 by kith             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEX_H
# define VERTEX_H

# include <stdalign.h>
# include "vector.h"

typedef struct	s_vertex
{
	alignas(16) union {
		struct {
			float	x;
			float	y;
			float	z;
		};
		t_vec3 vec;
	};
	union {
		float altitude;
		float w;
	};
}				t_vertex;

typedef struct	s_edge
{
	unsigned int start;
	unsigned int end;
}				t_edge;

#endif
