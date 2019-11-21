/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 00:10:15 by nbousset          #+#    #+#             */
/*   Updated: 2019/05/10 15:07:01 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

int		ft_stack_count(t_stack **stack)
{
	t_stack *elem;
	int		count;

	if (!stack || !*stack)
		return (0);
	count = 0;
	elem = *stack;
	while (elem != NULL)
	{
		count++;
		elem = elem->next;
	}
	return (count);
}
