/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarray_del.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 20:31:22 by nbousset          #+#    #+#             */
/*   Updated: 2019/05/16 20:31:26 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_strarray_del(char ***array)
{
	size_t	size;
	size_t	i;

	if (array && *array)
	{
		size = ft_strarray_len(*array);
		i = 0;
		while (i < size)
		{
			ft_memdel((void *)&(*array)[i]);
			i++;
		}
		ft_memdel((void **)(array));
	}
}
