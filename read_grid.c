/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:20:43 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/06 16:35:39 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "fdf.h"
#include "bitmap.h"

int		read_grid(int fd, t_list **rows)
{
	t_vertex	*row;
	char		**words;
	char		*line;
	int			count;
	int			i;
	int			j;

	j = 0;
	while (get_next_line(fd, &line) > 0)
	{
		words = ft_strsplit_n(line, ' ', &count);
		row = malloc(sizeof(t_vertex) * count);
		i = 0;
		while (i < count)
		{
			row[i].vec = make_float3(i, j, ft_atoi(words[i]));
			row[i].col = int_to_rgba(0);
			free(words[i]);
			i++;
		}
		ft_lstadd(rows, ft_lstnew(row, sizeof(t_vertex) * count));
		free(line);
		free(words);
		free(row);
		j++;
	}
	return (count);
}
