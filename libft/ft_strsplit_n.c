/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_n.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:47:01 by qsharoly          #+#    #+#             */
/*   Updated: 2019/10/03 18:19:50 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_split_info	get_split_info(char const *s, char c)
{
	t_split_info	info;
	char			*from;
	char			*till;

	info.elem_count = 0;
	info.source_len = ft_strlen(s);
	from = (char *)s;
	while (from < s + info.source_len)
	{
		till = ft_strchr(from, c);
		if (till == NULL)
			till = (char *)(s + info.source_len);
		till++;
		if (till - from > 1)
			info.elem_count++;
		from = till;
	}
	return (info);
}

static void			undo(char ***pointers, size_t k)
{
	size_t	i;

	i = 0;
	while (i < k)
	{
		free((*pointers)[i]);
		i++;
	}
	free(*pointers);
}

static void			ft_strsplit_job(char ***result,
		char const *s, char c, t_split_info info)
{
	char			*from;
	char			*till;
	unsigned int	k;

	k = 0;
	from = (char *)s;
	while (from < s + info.source_len)
	{
		till = ft_strchr(from, c);
		if (till == NULL)
			till = (char *)(s + info.source_len);
		till += 1;
		if (till - from > 1)
		{
			(*result)[k] = ft_strsub(from, 0, till - from - 1);
			if (!(*result)[k])
			{
				undo(result, k);
				return ;
			}
			k++;
		}
		from = till;
	}
	(*result)[info.elem_count] = NULL;
}

char				**ft_strsplit_n(char const *s, char c, int *count)
{
	t_split_info	info;
	char			**result;

	info = get_split_info(s, c);
	result = (char **)malloc((info.elem_count + 1) * sizeof(char **));
	if (result)
		ft_strsplit_job(&result, s, c, info);
	*count = info.elem_count;
	return (result);
}
