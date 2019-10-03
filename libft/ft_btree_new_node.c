/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_new_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:45:17 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/16 13:45:28 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree	*ft_btree_new_node(void const *content, size_t content_size)
{
	t_btree	*root;

	root = (t_btree *)malloc(sizeof(t_btree));
	if (root)
	{
		root->content = NULL;
		root->content_size = 0;
		root->left = NULL;
		root->right = NULL;
		if (content)
		{
			root->content = malloc(content_size);
			if (root->content)
			{
				ft_memcpy(root->content, content, content_size);
				root->content_size = content_size;
			}
			else
			{
				free(root);
				root = NULL;
			}
		}
	}
	return (root);
}
