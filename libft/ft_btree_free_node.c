/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_free_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 12:24:37 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/16 12:56:39 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_free_node(t_btree **tree, void (*del)(void *, size_t))
{
	del((*tree)->content, (*tree)->content_size);
	free(*tree);
	*tree = NULL;
}
