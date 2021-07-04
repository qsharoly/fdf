/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 11:53:14 by qsharoly          #+#    #+#             */
/*   Updated: 2021/07/04 00:44:26 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//returns the pointer to new last node for efficient adding in loop:
//t_list	*head = NULL;
//t_list	**tail = &head;
//while(data = get_data())
//{
//	tail = ft_lstadd_back(tail, ft_lstnew(data));
//}
t_list	**ft_lstadd_back(t_list **lst, t_list *new)
{
	if (new == NULL)
		return (NULL);
	if (!*lst)
		*lst = new;
	else
	{
		while ((*lst)->next)
			lst = &((*lst)->next);
		(*lst)->next = new;
	}
	return (lst);
}
