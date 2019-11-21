/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_insert_at.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

static int	insert(t_list *list, t_list_elem *new, int index)
{
	t_list_elem *elem;

	elem = ft_list_get_at(list, index);
	new->index = elem->index;
	ft_list_incr_index(list, index);
	elem->prev->next = new;
	new->prev = elem->prev;
	elem->prev = new;
	new->next = elem;
	list->count++;
	return (1);
}

int			ft_list_insert_at(t_list *list, const void *value, int index,
																ssize_t size)
{
	t_list_elem	*elem;

	if (!list)
		return (0);
	if (!(elem = ft_list_elem_new(value, size)))
		return (0);
	if (index <= 0)
		return (ft_list_add_front(list, elem));
	else if (index >= list->count)
		return (ft_list_add_back(list, elem));
	return (insert(list, elem, index));
}
