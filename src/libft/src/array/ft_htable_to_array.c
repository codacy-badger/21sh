/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htable_to_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static char	**alloc_array(size_t size)
{
	char	**array;

	if (!(array = (char **)ft_memalloc(sizeof(char *) * size)))
		return (NULL);
	return (array);
}

static char	*entry_to_str(t_hentry *entry)
{
	char	*str;
	size_t	key_len;
	size_t	val_len;

	key_len = ft_strlen(entry->key);
	val_len = ft_strlen(entry->value);
	if (!(str = (char *)ft_memalloc(key_len + val_len + 2)))
		return (NULL);
	ft_memcpy(str, entry->key, key_len);
	str[key_len] = ':';
	ft_memcpy(str + key_len + 1, entry->value, val_len);
	return (str);
}

char		**ft_htable_to_array(t_htable *htable)
{
	char		**array;
	t_hentry	*entry;
	size_t		i;
	size_t		j;

	if (!htable || !(array = alloc_array(htable->count + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (i < htable->size)
	{
		if ((entry = htable->table[i]) != NULL)
		{
			while (entry)
			{
				if (!(array[j++] = entry_to_str(entry)))
					return (NULL);
				entry = entry->next;
			}
		}
		i++;
	}
	array[j] = NULL;
	return (array);
}
