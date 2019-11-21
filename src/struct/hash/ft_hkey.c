/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hkey.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

t_uint32	ft_hkey(t_htable *htable, const char *key)
{
	t_uint64	index;
	t_uint64	p;

	if (!key)
		return (0);
	index = 0;
	p = (t_uint64)ft_nextprime(htable->size);
	while (*key)
	{
		index <<= 5;
		index += (t_uint64)(*key);
		key++;
	}
	index %= p;
	index %= (t_uint64)(htable->size);
	return ((t_uint32)index);
}
