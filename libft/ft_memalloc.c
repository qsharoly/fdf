/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:11:24 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/09 18:57:09 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*fresh;

	fresh = malloc(size);
	if (fresh == NULL)
		return (NULL);
	else
		return (ft_memset(fresh, 0, size));
}
