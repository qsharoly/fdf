/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_add_unique.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 12:02:25 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/16 18:01:35 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** if a node with identical content exists, return pointer to that,
** otherwise add new_node to the tree & return pointer to the new_node.
*/

t_btree	*ft_btree_add_unique(t_btree **tree, t_btree *new_node,
		int (*cmp)(void *, void *))
{
	int		diff;

	if (!(*tree))
	{
		(*tree) = new_node;
		return (*tree);
	}
	diff = cmp((*tree)->content, new_node->content);
	if (diff < 0)
		return (ft_btree_add_unique(&(*tree)->right, new_node, cmp));
	else if (diff > 0)
		return (ft_btree_add_unique(&(*tree)->left, new_node, cmp));
	return (*tree);
}
