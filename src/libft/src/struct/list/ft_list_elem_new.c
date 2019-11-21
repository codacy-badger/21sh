/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_elem_new.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

t_list_elem	*ft_list_elem_new(const void *content, ssize_t content_size)
{
	t_list_elem	*elem;

	if (!(elem = (t_list_elem	*)ft_memalloc(sizeof(*elem))))
		return (NULL);
	if (content == NULL || content_size == 0)
	{
		elem->content = (void *)content;
		elem->type = PTR;
	}
	else
	{
		if (content_size < 0)
			content_size = ft_strlen(content);
		if (!(elem->content = ft_memalloc(content_size + 1)))
		{
			ft_memdel((void *)&elem);
			return (NULL);
		}
		ft_memcpy(elem->content, content, content_size);
		elem->type = CPY;
	}
	elem->content_size = content_size;
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}
