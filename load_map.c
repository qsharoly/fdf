/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:20:43 by qsharoly          #+#    #+#             */
/*   Updated: 2021/07/04 01:04:45 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "fdf.h"
#include "bitmap.h"

void	del_map_row(void *row)
{
	free(row);
}

static char	*next_entry(char *cur)
{
	while (*cur && *cur != ' ')
		cur++;
	while (*cur && *cur == ' ')
		cur++;
	return (cur);
}

static int	count_entries(const char *line)
{
	char	*cur;
	int		count;

	count = 0;
	cur = (char *)line;
	while (*cur)
	{
		cur = next_entry(cur);
		count++;
	}
	return (count);
}

static t_vertex	*read_row(int j, const char *line, int *count)
{
	t_vertex	*row;
	char		*cur;
	int			i;
	static char	wait_anim[4][4] = {"[-]", "[\\]", "[|]", "[/]"};

	if (j % 40 == 0)
	{
		ft_putstr_fd("\033[16DLoading map: ", 2);
		ft_putstr_fd(wait_anim[j / 40 % 4], 2);
	}
	*count = count_entries(line);
	row = malloc(sizeof(*row) * *count);
	if (!row)
		return (NULL);
	i = 0;
	cur = (char *)line;
	while (i < *count)
	{
		row[i] = (t_vertex){ .vec = {i, j, ft_atoi(cur)}, .color = 0x00000000 };
		cur = next_entry(cur);
		i++;
	}
	return (row);
}

static int	rg_abort(t_list **rows, char *line, t_vertex *row,
					char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_lstclear(rows, del_map_row);
	free(line);
	free(row);
	return (-2);
}

int	load_map(int fd, t_map *map)
{
	t_vertex	*row;
	t_list		**tail_ptr;
	char		*line;
	int			count;
	int			j;
	int			gnl_status;

	j = 0;
	line = NULL;
	tail_ptr = &map->rows;
	while ((gnl_status = get_next_line(fd, &line)) > 0)
	{
		row = read_row(j, line, &count);
		if (!row)
			return (rg_abort(&map->rows, line, row, "\nalloc fail.\n"));
		if (j == 0)
			map->row_size = count;
		else if (count != map->row_size)
		{
			ft_putstr_fd("\nrow ", 2);
			ft_putnbr_fd(j, 2);
			return (rg_abort(&map->rows, line, row, " has bad length.\n"));
		}
		tail_ptr = ft_lstadd_back(tail_ptr, ft_lstnew(row));
		if (!tail_ptr)
			return (rg_abort(&map->rows, line, row, "\nalloc fail.\n"));
		j++;
		map->row_num++;
	}
	free(line);
	return (gnl_status);
}
