/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

t_bool	ft_list_add_back(t_list *list, t_list_elem *new)
{
	t_list_elem	*first;
	t_list_elem	*last;

	if (!list || !new)
		return (false);
	if (list->elems == NULL)
		return (ft_list_add_front(list, new));
	first = ft_list_get_first(list);
	last = ft_list_get_last(list);
	new->prev = last;
	last->next = new;
	if (list->circular)
	{
		new->next = first;
		first->prev = new;
	}
	new->index = last->index + 1;
	list->count++;
	return (true);
}
