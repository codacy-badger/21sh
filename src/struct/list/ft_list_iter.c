/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_iter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	ft_list_iter(t_list *list, int start, int end, void (*f)(t_list_elem *))
{
	t_list_elem	*elem;

	if (!list || !(elem = list->elems))
		return ;
	while (elem->index < start)
		elem = elem->next;
	if (end < 0 || end < start)
		end = list->count;
	while (start < end)
	{
		f(elem);
		elem = elem->next;
		end--;
	}
}
