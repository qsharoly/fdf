/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:45:11 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/20 18:59:11 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static char		*enlarge(char *line, size_t *size, size_t new_size)
{
	char	*fresh;

	fresh = (char *)ft_memalloc(new_size);
	if (fresh == NULL)
	{
		free(line);
		return (NULL);
	}
	ft_memcpy(fresh, line, *size);
	free(line);
	*size = new_size;
	return (fresh);
}

static ssize_t	parse_realloc(t_buf *buf, char **line,
					size_t *linelen, size_t *my_size)
{
	char		*from;
	char		*till;
	size_t		part_size;
	size_t		new_size;

	from = (buf->delim_pos == NULL) ? buf->data
									: buf->delim_pos + 1;
	buf->delim_pos = (char *)ft_memchr(from, '\n',
			(buf->data + buf->len) - from);
	till = (buf->delim_pos == NULL) ? buf->data + buf->len
									: buf->delim_pos;
	part_size = till - from;
	if (part_size > SIZE_MAX - *linelen)
		return (-1);
	new_size = *my_size;
	while (part_size > new_size - *linelen - 1)
		new_size = new_size * 2;
	if (new_size != *my_size)
		*line = enlarge(*line, my_size, new_size);
	if (*line == NULL)
		return (-1);
	ft_memcpy(*line + *linelen, from, till - from);
	*linelen += part_size;
	*(*line + *linelen) = '\0';
	return (part_size);
}

static t_buf	*get_buffer_by_fd(const int fd, t_list **buffers)
{
	t_list	*ptr;
	t_buf	new_buf;

	ptr = *buffers;
	while (ptr)
	{
		if (fd == ((t_buf *)ptr->content)->fd)
			return (ptr->content);
		ptr = ptr->next;
	}
	new_buf.fd = fd;
	new_buf.delim_pos = NULL;
	new_buf.len = 0;
	ft_lstadd(buffers, ft_lstnew(&new_buf, sizeof(t_buf)));
	return ((*buffers)->content);
}

static void		remove_buffer_by_fd(const int fd, t_list **linus)
{
	t_list	*next;

	while (((t_buf *)(*linus)->content)->fd != fd)
		linus = &((*linus)->next);
	next = (*linus)->next;
	free((*linus)->content);
	free(*linus);
	*linus = next;
}

/*
** in get_next_line():
** because || stops evaluating when it finds first true condition,
** when buf.delim_pos is not null, reading will not occur!
** We will continue to parse what already is in the buffer.
*/

int				get_next_line(const int fd, char **line)
{
	static t_list	*buffers;
	t_buf			*buf;
	static size_t	my_size = BUFF_SIZE;
	size_t			linelen;

	if (fd < 0)
		return (-1);
	linelen = 0;
	if (*line == NULL)
		*line = (char *)ft_memalloc(my_size * sizeof(char));
	buf = get_buffer_by_fd(fd, &buffers);
	while (buf && (buf->delim_pos != NULL
			|| (buf->len = read(fd, buf->data, BUFF_SIZE)) > 0))
	{
		if (parse_realloc(buf, line, &linelen, &my_size) < 0)
			return (-1);
		if (buf->delim_pos != NULL)
			break ;
	}
	if (buf == NULL || buf->len == -1)
		return (-1);
	else if (buf->len > 0 || linelen > 0)
		return (1);
	remove_buffer_by_fd(fd, &buffers);
	return (0);
}
