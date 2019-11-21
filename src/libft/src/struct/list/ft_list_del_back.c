/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_del_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	ft_list_del_back(t_list *list, void (*del)(void *, size_t))
{
	t_list_elem	*elem;

	if (!list || !(elem = ft_list_get_last(list)))
		return ;
	if (elem->prev)
		elem->prev->next = elem->next;
	if (elem->next)
		elem->next->prev = elem->prev;
	ft_list_elem_del(&elem, del);
	if (list->count == 1)
		list->elems = NULL;
	list->count--;
}
