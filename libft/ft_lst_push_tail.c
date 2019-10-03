/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_tail.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsharoly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 11:53:14 by qsharoly          #+#    #+#             */
/*   Updated: 2019/09/16 11:55:57 by qsharoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_push_tail(t_list **alst, t_list *new_node)
{
	t_list	*ptr;

	if (!(*alst))
	{
		(*alst) = new_node;
		return ;
	}
	else
	{
		ptr = (*alst);
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_node;
	}
}
