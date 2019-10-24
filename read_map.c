/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:20:43 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/24 18:01:37 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "fdf.h"
#include "bitmap.h"

void			lst_del_fdf_row(void *row, size_t size)
{
	if (!row || size == 0)
		return ;
	free(row);
}

static t_vertex	*read_row(int j, char *line, int *count)
{
	t_vertex	*row;
	char		**words;
	int			i;

	if ((words = ft_strsplit_n(line, ' ', count)))
		if ((row = malloc(sizeof(t_vertex) * *count)))
		{
			i = 0;
			while (i < *count)
			{
				row[i].vec = make_float3(i, j, ft_atoi(words[i]));
				row[i].col = int_to_rgba(0);
				free(words[i]);
				i++;
			}
			free(words);
			return (row);
		}
	return (NULL);
}

static int		rg_abort(t_list **rows, char *line, t_vertex *row,
					char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" abort file read.\n", 2);
	ft_lstdel(rows, lst_del_fdf_row);
	free(line);
	free(row);
	return (-2);
}

int				read_map(int fd, t_map *map)
{
	t_vertex	*row;
	char		*line;
	int			count;
	int			j;
	int			gnl_status;

	j = 0;
	line = NULL;
	while ((gnl_status = get_next_line(fd, &line)) > 0)
	{
		if (!(row = read_row(j, line, &count)))
			return (rg_abort(&map->rows, line, row, "alloc fail."));
		if (j == 0)
			map->row_size = count;
		else if (count != map->row_size)
			return (rg_abort(&map->rows, line, row, "bad line length."));
		if (!(ft_lst_push_tail(&map->rows,
					ft_lstnew(row, sizeof(t_vertex) * count))))
			return (rg_abort(&map->rows, line, row, "alloc fail."));
		free(row);
		j++;
	}
	map->row_num = j;
	free(line);
	return (gnl_status);
}
