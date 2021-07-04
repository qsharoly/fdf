/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 22:15:18 by qsharoly          #+#    #+#             */
/*   Updated: 2021/07/03 07:10:22 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_entries(const char *line, char delim)
{
	int			count;
	const char	*cur;

	cur = line;
	count = 0;
	while (*cur)
	{
		while (*cur && *cur == delim)
			cur++;
		if (*cur)
			count++;
		while (*cur && *cur != delim)
			cur++;
	}
	return (count);
}

static void	release(char **result)
{
	while (*result)
	{
		free(*result);
		result++;
	}
	free(result);
}

char **ft_split(char const *s, char delim)
{
	char		**result;
	const char	*cur;
	const char	*mark;
	int			count;
	int			k;

	count = count_entries(s, delim);
	result = malloc((count + 1) * sizeof(*result));
	if (!result)
		return (NULL);
	k = 0;
	mark = NULL;
	cur = s;
	while (k < count)
	{
		while (*cur && *cur == delim)
			cur++;
		if (*cur)
			mark = cur;
		while (*cur && *cur != delim)
			cur++;
		if (mark && cur > mark)
		{
			result[k] = malloc((cur - mark + 1) * sizeof(**result));
			if (!result[k])
			{
				release(result);
				return (NULL);
			}
			ft_memcpy(result[k], mark, cur - mark);
			result[k][cur - mark] = '\0';
			k++;
		}
	}
	result[count] = NULL;
	return (result);
}
