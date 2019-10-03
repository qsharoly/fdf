/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:20:43 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/03 19:00:23 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "fdf.h"

int		read_grid(int fd, t_list **rows)
{
	t_float3	*row;
	char		**words;
	char		*line;
	int			count;
	int			i;
	int			j;

	j = 0;
	while (get_next_line(fd, &line) > 0)
	{
		words = ft_strsplit_n(line, ' ', &count);
		row = malloc(sizeof(t_float3) * count);
		i = 0;
		while (i < count)
		{
			row[i].x = i;
			row[i].y = j;
			row[i].z = ft_atoi(words[i]);
			free(words[i]);
			i++;
		}
		ft_lstadd(rows, ft_lstnew(row, sizeof(t_float3) * count));
		free(line);
		free(words);
		free(row);
		j++;
	}
	return (count);
}
