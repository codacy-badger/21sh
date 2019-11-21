/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_add_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/11/22 00:26:12 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

static bool	list_empty_add(t_list *list, t_list_elem *new)
{
	list->elems = new;
	if (list->circular)
	{
		new->prev = new;
		new->next = new;
	}
	list->count++;
	return (true);
}

bool			ft_list_add_front(t_list *list, t_list_elem *new)
{
	t_list_elem	*first;
	t_list_elem	*last;

	if (!list || !new)
		return (false);
	if (list->elems == NULL)
		return (list_empty_add(list, new));
	first = ft_list_get_first(list);
	last = ft_list_get_last(list);
	ft_list_incr_index(list, first->index);
	new->next = first;
	first->prev = new;
	if (list->circular)
	{
		new->prev = last;
		last->next = new;
	}
	list->elems = new;
	list->count++;
	return (true);
}
