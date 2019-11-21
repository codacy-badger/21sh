/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htdelone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	ft_htdelone(t_htable *htable, const char *key)
{
	t_hentry	*entry;

	if ((entry = ft_htget(htable, key)) != NULL)
	{
		if (entry->prev)
			entry->prev->next = entry->next;
		else
			*entry->head = entry->next;
		if (entry->next)
			entry->next->prev = entry->prev;
		ft_hentrydel(&entry);
		htable->count--;
	}
}
