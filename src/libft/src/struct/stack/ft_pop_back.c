/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:03:00 by nbousset          #+#    #+#             */
/*   Updated: 2019/04/23 18:42:11 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	ft_pop_back(t_stack **stack, void (*del)(void *))
{
	t_stack	*prev;
	t_stack	*elem;

	if (stack && *stack)
	{
		if (ft_stack_count(stack) == 1)
			return (ft_pop(stack, del));
		elem = *stack;
		while (elem->next)
		{
			prev = elem;
			elem = elem->next;
		}
		if (prev)
			prev->next = NULL;
		if (del)
			del(elem->content);
		else
			ft_memdel((void *)&elem->content);
		ft_memdel((void *)&elem);
	}
}
