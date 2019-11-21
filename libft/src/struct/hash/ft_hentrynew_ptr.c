/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hentrynew_ptr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

t_hentry	*ft_hentrynew_ptr(const char *key, const void *value)
{
	t_hentry	*entry;

	if (!key)
		return (NULL);
	if (!(entry = ft_memalloc(sizeof(*entry))))
		return (NULL);
	if (!(entry->key = ft_memalloc(ft_strlen(key) + 1)))
	{
		ft_memdel((void *)&entry);
		return (NULL);
	}
	ft_strcpy(entry->key, key);
	entry->value = (void *)value;
	entry->prev = NULL;
	entry->next = NULL;
	entry->type = PTR;
	return (entry);
}
