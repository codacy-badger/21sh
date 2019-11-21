/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dequeue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:03:00 by nbousset          #+#    #+#             */
/*   Updated: 2019/04/23 18:42:11 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	ft_dequeue(t_queue **queue, void (*del)(void *))
{
	t_queue	*elem;

	if (queue && *queue)
	{
		elem = *queue;
		*queue = elem->next;
		if (del)
			del(elem->content);
		else
			ft_memdel((void *)&elem->content);
		ft_memdel((void *)&elem);
	}
}
