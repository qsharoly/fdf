/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:14:23 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/11 13:48:15 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*fresh;

	fresh = (t_list *)malloc(sizeof(t_list));
	if (fresh)
	{
		fresh->content = NULL;
		fresh->content_size = 0;
		fresh->next = NULL;
		if (content)
		{
			fresh->content = malloc(content_size);
			if (fresh->content)
			{
				ft_memcpy(fresh->content, content, content_size);
				fresh->content_size = content_size;
			}
			else
			{
				free(fresh);
				fresh = NULL;
			}
		}
	}
	return (fresh);
}
