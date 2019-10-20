/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:20:43 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/20 19:56:17 by qsharoly         ###   ########.fr       */
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

static int		free_everything(t_list **rows, char *line, t_vertex *row,
					char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_lstdel(rows, lst_del_fdf_row);
	free(line);
	free(row);
	return (-1);
}

int				read_grid(int fd, t_list **rows)
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
		if ((row = read_row(j, line, &count)))
		{
			if (ft_lst_push_tail(rows,
						ft_lstnew(row, sizeof(t_vertex) * count)))
				free(row);
			else
				return (free_everything(rows, line, row, "alloc fail.\n"));
		}
		else
			return (free_everything(rows, line, row, "alloc fail.\n"));
		j++;
	}
	free(line);
	return (gnl_status);
}
