/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarray_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 20:31:22 by nbousset          #+#    #+#             */
/*   Updated: 2019/05/16 20:31:26 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	**ft_strarray_dup(char **array)
{
	char	**dup;
	size_t	size;
	size_t	i;

	size = ft_strarray_len(array);
	if (!(dup = (char **)ft_memalloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (!(dup[i] = ft_strdup(array[i])))
			return (NULL);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
