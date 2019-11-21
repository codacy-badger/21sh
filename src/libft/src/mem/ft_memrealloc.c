/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 00:37:27 by nbousset          #+#    #+#             */
/*   Updated: 2019/05/10 00:37:49 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memrealloc(void *m, size_t old_size, size_t new_size)
{
	void	*new;

	new = NULL;
	if (new_size < old_size)
		old_size = new_size;
	else if (new_size == old_size)
		return (m);
	if (!(new = ft_memalloc(new_size + 1)))
		return (NULL);
	if (m)
	{
		ft_memcpy(new, m, old_size);
		ft_bzero(m, old_size);
		ft_memdel(&m);
	}
	return (new);
}
