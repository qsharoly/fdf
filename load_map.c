/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:20:43 by qsharoly          #+#    #+#             */
/*   Updated: 2021/06/30 20:23:40 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "fdf.h"
#include "bitmap.h"

void	lst_del_fdf_row(void *row, size_t size)
{
	if (!row || size == 0)
		return ;
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
	row = malloc(sizeof(t_vertex) * *count);
	if (!row)
		return (NULL);
	i = 0;
	cur = (char *)line;
	while (i < *count)
	{
		row[i].vec = (t_vec3){i, j, ft_atoi(cur)};
		row[i].col = 0x00000000;
		cur = next_entry(cur);
		i++;
	}
	return (row);
}

static int	rg_abort(t_list **rows, char *line, t_vertex *row,
					char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" abort file read.\n", 2);
	ft_lstdel(rows, lst_del_fdf_row);
	free(line);
	free(row);
	return (-2);
}

int	load_map(int fd, t_map *map)
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
