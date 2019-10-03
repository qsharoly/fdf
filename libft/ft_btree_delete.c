/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_delete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 12:27:11 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/16 12:31:03 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_delete(t_btree **tree, void (*del)(void *, size_t))
{
	if ((*tree)->left == NULL && (*tree)->right == NULL)
		ft_btree_free_node(tree, del);
	else
	{
		ft_btree_delete(&((*tree)->right), del);
		ft_btree_delete(&((*tree)->left), del);
		ft_btree_free_node(tree, del);
	}
}
