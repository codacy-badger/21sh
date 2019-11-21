/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htclr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	ft_htclr(t_htable *htable)
{
	t_hentry	**table;
	t_hentry	*entry;
	t_hentry	*tmp;
	size_t		i;

	table = htable->table;
	i = 0;
	while (i < htable->size)
	{
		if ((entry = table[i]))
		{
			while (entry)
			{
				tmp = entry->next;
				ft_hentrydel(&table[i]);
				htable->count--;
				entry = tmp;
			}
		}
		i++;
	}
}
