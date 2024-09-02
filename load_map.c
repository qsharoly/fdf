/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:20:43 by qsharoly          #+#    #+#             */
/*   Updated: 2024/09/03 02:02:29 by kith             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

static int	is_signed_int(char c)
{
	return (ft_isdigit(c) || c == '-');
}

static int	is_color(char c)
{
	return (c == 'x' || ft_isdigit(c) || ('a' <= c && c <= 'f'));
}

static int	is_comma(char c)
{
	return (c == ',');
}

static int	is_vertex(char c)
{
	return (is_signed_int(c) || is_comma(c) || is_color(ft_tolower(c)));
}

static int	is_newline(char c)
{
	return (c == '\n');
}

static int	is_map_character(char c)
{
	return (is_space(c) || is_vertex(c) || is_newline(c));
}

typedef struct
{
	const char	*chars;
	int			size;
}	t_sv;

static t_sv	chop_while(t_sv *sv, int (*condition)(char c))
{
	t_sv	out;

	int		i = 0;
	while (i < (*sv).size && condition((*sv).chars[i]))
		i++;
	out = (t_sv){ (*sv).chars, i };
	*sv = (t_sv){ (*sv).chars + i, (*sv).size - i };
	return (out);
}

static t_sv	chop_int(t_sv *sv)
{
	return (chop_while(sv, is_signed_int));
}

static int	parse_int(t_sv sv)
{
	int	n = 0;
	int i = 0;
	int	neg = 1;

	if (i < sv.size && sv.chars[0] == '-')
	{
		i++;
		neg = -1;
	}
	while (i < sv.size && ft_isdigit(sv.chars[i]))
	{
		n = n * 10 + sv.chars[i] - '0';
		i++;
	}
	return (n * neg);
}

static void	skip_while(t_sv *sv, int (*condition)(char c))
{
	int	i = 0;
	while (i < (*sv).size && condition((*sv).chars[i]))
		i++;
	*sv = (t_sv){ (*sv).chars + i, (*sv).size - i };
}

static void	skip_single_char(t_sv *sv)
{
	if ((*sv).size)
		*sv = (t_sv){ (*sv).chars + 1, (*sv).size - 1 };
}

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int load_map(const char *filename, t_map *map)
{
	int			ok;
	int			fd;
	struct stat	statbuf;
	char		*file_memory;
	int			file_size;
	int			vertex_count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		dprintf(2, "'%s': cannot open map file.\n", filename);
		return (FAIL);
	}
	ok = fstat(fd, &statbuf);
	if (ok < 0)
	{
		dprintf(2, "cannot load map: fstat failed.\n");
		return (FAIL);
	}
	file_size = statbuf.st_size;
    file_memory = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);
	if (!file_memory)
	{
		dprintf(2, "cannot load map: mmap failed.\n");
		return (FAIL);
	}
	printf("Loading '%s': ", filename);
	// first pass: calculate map dimensions
	{
		t_sv input = { .chars = file_memory, .size = file_size };
		vertex_count = 0;
		int	line = 0;
		int	verts_per_line = 0;
		while (input.size)
		{
			if (!is_map_character(input.chars[0]))
			{
				dprintf(2, "error: bad character in map file: '%c'\n", input.chars[0]);
				munmap(file_memory, file_size);
				return (FAIL);
			}
			skip_while(&input, is_space);
			t_sv sv = chop_while(&input, is_vertex);
			if (sv.size)
				vertex_count++;
			if (input.size == 0 || is_newline(input.chars[0]))
			{
				if (line == 0)
					verts_per_line = vertex_count;
				if (line > 0 && (vertex_count % verts_per_line != 0))
				{
					dprintf(2, "error: Map is not rectangular: Line %d has %d entries (want %d)\n",
							line, vertex_count % verts_per_line, verts_per_line);
					munmap(file_memory, file_size);
					return (FAIL);
				}
				line++;
				skip_single_char(&input);
			}
		}
		if (vertex_count == 0)
		{
			dprintf(2, "error: Map is empty.\n");
			munmap(file_memory, file_size);
			return (FAIL);
		}
		map->per_row = verts_per_line;
		map->rows = vertex_count / verts_per_line;
	}
	printf("%dx%d ", map->rows, map->per_row);

	int vertices_size = vertex_count * sizeof(*map->vertices);
	int projected_size = vertex_count * sizeof(*map->projected);
	map->edges_count = map->per_row * (map->rows - 1) + (map->per_row - 1) * map->rows;
	int edges_size = map->edges_count * sizeof(*map->edges);
	char *map_memory = malloc(vertices_size + projected_size + edges_size);
	if (!map_memory) {
		dprintf(2, "error: allocation failed\n");
		munmap(file_memory, file_size);
		return (FAIL);
	}
	map->vertices = (t_vertex *)map_memory;
	map->projected = (t_vertex *)(map_memory + vertices_size);
	map->edges = (t_edge *)(map_memory + vertices_size + projected_size);

	// second pass: actually parse the map & load into vertices array
	{
		int x = 0;
		int y = 0;
		int j = 0;
		t_sv input = (t_sv){ .chars = file_memory, .size = file_size };
		while (input.size)
		{
			skip_while(&input, is_space);
			t_sv sv_vert = chop_while(&input, is_vertex);
			t_sv sv_z = chop_int(&sv_vert);
			if (sv_z.size)
			{
				int z = parse_int(sv_z);
				map->vertices[j] = (t_vertex){ .vec = {x, y, z} };
				j++;
				x++;
			}
			if (is_newline(input.chars[0]))
			{
				x = 0;
				y++;
				skip_single_char(&input);
			}
		}
	}
	munmap(file_memory, file_size);
	// find z value range
	map->z_min = +INFINITY;
	map->z_max = -INFINITY;
	{
		int j = 0;
		while (j < vertex_count)
		{
			map->z_min = fmin(map->vertices[j].vec.z, map->z_min);
			map->z_max = fmax(map->vertices[j].vec.z, map->z_max);
			++j;
		}
	}
	// setup relative altitudes of verts, scaled to [0.0, 1.0] interval
	{
		int j = 0;
		while (j < vertex_count)
		{
			if (map->z_max - map->z_min != 0.)
			{
				map->vertices[j].altitude = (map->vertices[j].z - map->z_min)/(map->z_max - map->z_min);
			}
			else
			{
				map->vertices[j].altitude = 0.5;
			}
			++j;
		}
	}
	// setup edges
	{
		int	i;
		int	j;
		int	current;
		t_edge *edges = map->edges;
		int map_per_row = map->per_row;
		int map_rows = map->rows;

		current = 0;
		j = 0;
		while (j < map_rows)
		{
			i = 0;
			while (i < map_per_row)
			{
				if (i < map_per_row - 1)
				{
					edges[current].start = i + j * map_per_row;
					edges[current].end = (i + 1) + j * map_per_row;
					current++;
				}
				if (j < map_rows - 1)
				{
					edges[current].start = i + j * map_per_row;
					edges[current].end = i + (j + 1) * map_per_row;
					current++;
				}
				i++;
			}
			j++;
		}
	}
	printf("ok.\n");
	return (OK);
}
