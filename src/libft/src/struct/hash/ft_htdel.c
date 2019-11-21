/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htdel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void		ft_htdel(t_htable **ahtable)
{
	t_uint32	i;
	t_hentry	*entry;
	t_hentry	*next;

	i = 0;
	if (!ahtable || !*ahtable)
		return ;
	while (i < (*ahtable)->size)
	{
		entry = (*ahtable)->table[i];
		while (entry)
		{
			next = entry->next;
			ft_hentrydel(&entry);
			entry = next;
		}
		i++;
	}
	ft_memdel((void **)&(*ahtable)->table);
	ft_memdel((void **)ahtable);
}
