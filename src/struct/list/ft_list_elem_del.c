/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_elem_del.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	ft_list_elem_del(t_list_elem **elem, void (*del)(void *, size_t))
{
	if (!elem || !*elem)
		return ;
	if ((*elem)->type == PTR)
		(*elem)->content = NULL;
	else
	{
		if (del)
			del((*elem)->content, (*elem)->content_size);
		else
			ft_memdel((void *)&(*elem)->content);
	}
	(*elem)->next = NULL;
	(*elem)->prev = NULL;
	ft_memdel((void *)elem);
}
