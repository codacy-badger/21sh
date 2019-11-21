/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:03:00 by nbousset          #+#    #+#             */
/*   Updated: 2019/04/23 18:42:11 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	ft_push(t_stack **stack, t_stack *new)
{
	if (stack && new)
	{
		if (!(*stack))
			*stack = new;
		else
		{
			new->next = *stack;
			*stack = new;
		}
	}
}
