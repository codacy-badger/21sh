/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarray_to_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

t_list	*ft_strarray_to_list(char **array, int size,
											char circular, char alloc)
{
	t_list	*list;
	int		i;

	if (size < 0)
		size = 0;
	list = ft_list_new(circular);
	if (array)
	{
		i = 0;
		while (i < size)
			ft_list_insert_at(list, array[i++], list->count, alloc ? -1 : 0);
	}
	return (list);
}
