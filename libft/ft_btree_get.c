/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:04:31 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/16 15:18:23 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** return pointer to the node for which comparison function returns 0
** if not found, return NULL.
*/

t_btree	*ft_btree_get(t_btree *tree, void *needle,
		int (*cmp)(void *, void *))
{
	int		diff;

	if (!tree)
	{
		return (NULL);
	}
	diff = cmp(tree->content, needle);
	if (diff < 0)
		return (ft_btree_get(tree->right, needle, cmp));
	else if (diff > 0)
		return (ft_btree_get(tree->left, needle, cmp));
	return (tree);
}
