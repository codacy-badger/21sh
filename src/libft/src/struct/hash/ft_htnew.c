/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htnew.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

t_htable	*ft_htnew(t_uint32 size)
{
	t_htable	*htable;
	t_uint32	i;

	if (size == 0)
		return (NULL);
	if (!(htable = ft_memalloc(sizeof(t_htable))))
		return (NULL);
	if (!(htable->table = (t_hentry **)ft_memalloc(sizeof(t_hentry *) * size)))
	{
		ft_memdel((void *)&htable);
		return (NULL);
	}
	i = 0;
	while (i < size)
		htable->table[i++] = NULL;
	htable->size = size;
	return (htable);
}
