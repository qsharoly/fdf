/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:06:18 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/12 17:16:33 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEX_H
# define VERTEX_H

# include "vector.h"
# include "bitmap.h"

typedef struct	s_vertex
{
	t_vec3		vec;
	t_rgba		col;
}				t_vertex;

#endif
