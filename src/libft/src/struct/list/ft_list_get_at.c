/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_get_at.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

t_list_elem	*ft_list_get_at(t_list *list, int index)
{
	t_list_elem	*elem;

	if (!list)
		return (NULL);
	if (index <= 0)
		return (ft_list_get_first(list));
	else if (index >= list->count - 1)
		return (ft_list_get_last(list));
	elem = list->elems;
	while (elem->index < index)
		elem = elem->next;
	return (elem);
}
