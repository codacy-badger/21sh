/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htget.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

t_hentry		*ft_htget(t_htable *htable, const char *key)
{
	t_uint32	index;
	t_hentry	*entry;

	if (!htable)
		return (NULL);
	index = ft_hkey(htable, key);
	entry = htable->table[index];
	if (entry == NULL)
		return (NULL);
	while (entry && !ft_strequ(entry->key, key))
		entry = entry->next;
	return (entry);
}
