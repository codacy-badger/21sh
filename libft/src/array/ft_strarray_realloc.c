/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarray_realloc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 20:31:22 by nbousset          #+#    #+#             */
/*   Updated: 2019/05/16 20:31:26 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	**ft_strarray_realloc(char **array, size_t new_size)
{
	char	**new_array;
	size_t	size;
	size_t	i;

	size = ft_strarray_len(array);
	if (!(new_array = (char **)ft_xmalloc(sizeof(char *) * (new_size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (!(new_array[i] = ft_strdup(array[i])))
			return (NULL);
		i++;
	}
	while (i < new_size)
		new_array[i] = NULL;
	ft_strarray_del(&array);
	return (new_array);
}
