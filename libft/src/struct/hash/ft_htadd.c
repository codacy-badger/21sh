/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htadd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

static int	ft_hentry_overwrite(t_hentry *entry, const char *value)
{
	if (!entry)
		return (-1);
	if (entry->type == PTR)
		entry->value = (void *)value;
	else if (entry->type == CPY)
	{
		if (!value)
			return (-1);
		ft_memdel((void **)&entry->value);
		if (!(entry->value = ft_xmalloc(ft_strlen(value) + 1)))
			return (-1);
		ft_strcpy(entry->value, value);
	}
	return (0);
}

static int	insert_entry(t_htable *htable, t_hentry *entry, t_uint32 index)
{
	t_hentry	*tmp;

	if (!htable || !entry || (index >= htable->size))
		return (-1);
	if ((tmp = htable->table[index]))
	{
		while (tmp->next)
			tmp = tmp->next;
		entry->prev = tmp;
		tmp->next = entry;
	}
	else
		htable->table[index] = entry;
	entry->head = &htable->table[index];
	htable->count++;
	return (0);
}

int			ft_htadd(t_htable *htable, const char *key,
											const void *value, ssize_t size)
{
	t_uint32	index;
	t_hentry	*entry;

	if (!htable)
		return (-1);
	index = ft_hkey(htable, key);
	if ((entry = ft_htget(htable, key)) != NULL)
		return (ft_hentry_overwrite(entry, value));
	if (size < 0 && value)
		size = ft_strlen((char *)value);
	if (size == 0)
		entry = ft_hentrynew_ptr(key, value);
	else
		entry = ft_hentrynew_cpy(key, value, (size_t)size);
	if (insert_entry(htable, entry, index) == -1)
		return (-1);
	return (0);
}
