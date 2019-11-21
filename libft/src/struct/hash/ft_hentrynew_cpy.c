/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hentrynew_cpy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

t_hentry	*ft_hentrynew_cpy(const char *key, const void *value, size_t size)
{
	t_hentry	*entry;

	if (!key || !value)
		return (NULL);
	if (!(entry = (t_hentry *)ft_memalloc(sizeof(*entry))))
		return (NULL);
	if (!(entry->key = (char *)ft_memalloc(ft_strlen(key) + 1)))
	{
		ft_memdel((void **)&entry);
		return (NULL);
	}
	if (!(entry->value = ft_memalloc(size + 1)))
	{
		ft_memdel((void **)&entry->key);
		ft_memdel((void **)&entry);
		return (NULL);
	}
	ft_strcpy(entry->key, key);
	ft_memcpy(entry->value, value, size);
	entry->prev = NULL;
	entry->next = NULL;
	entry->type = CPY;
	return (entry);
}
