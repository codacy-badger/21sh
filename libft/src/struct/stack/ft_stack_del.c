/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:03:00 by nbousset          #+#    #+#             */
/*   Updated: 2019/04/23 18:42:11 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	ft_stack_del(t_stack **stack, void (*del)(void *))
{
	if (!stack)
		return ;
	while (*stack)
		ft_pop(stack, del);
}
