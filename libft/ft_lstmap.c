/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:07:27 by qsharoly          #+#    #+#             */
/*   Updated: 2021/07/03 05:26:47 by debby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*node;
	void	*content;

	if (!lst || !f)
		return (NULL);
	content = f(lst->content);
	if (!content)
		return (NULL);
	head = ft_lstnew(content);
	if (!head)
	{
		del(content);
		return (NULL);
	}
	node = head;
	lst = lst->next;
	while (lst)
	{
		content = f(lst->content);
		if (!content)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		node->next = ft_lstnew(content);
		if (!node->next)
		{
			del(content);
			ft_lstclear(&head, del);
			return (NULL);
		}
		node = node->next;
		lst = lst->next;
	}
	return (head);
}
