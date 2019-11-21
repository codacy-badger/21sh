/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enqueue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:03:00 by nbousset          #+#    #+#             */
/*   Updated: 2019/04/23 18:42:11 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

#include <stdio.h>

void	ft_enqueue(t_queue **queue, t_queue *new)
{
	t_queue	*elem;

	if (queue && new)
	{
		if (!(*queue))
			*queue = new;
		else
		{
			elem = *queue;
			while (elem->next)
				elem = elem->next;
			elem->next = new;
		}
	}
}
