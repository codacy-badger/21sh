/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_del_at.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	ft_list_del_at(t_list *list, int index, void (*del)(void *, size_t))
{
	t_list_elem *elem;

	if (!list)
		return ;
	if (index >= (list->count - 1))
		return (ft_list_del_back(list, del));
	else if (index <= 0)
		return (ft_list_del_front(list, del));
	else if (!(elem = ft_list_get_at(list, index)))
		return ;
	ft_list_decr_index(list, index + 1);
	elem->prev->next = elem->next;
	elem->next->prev = elem->prev;
	ft_list_elem_del(&elem, del);
	list->count--;
}
