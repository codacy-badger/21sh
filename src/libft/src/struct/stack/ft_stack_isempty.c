/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_isempty.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 00:10:15 by nbousset          #+#    #+#             */
/*   Updated: 2019/05/10 15:07:01 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

int			ft_stack_isempty(t_stack **stack)
{
	if (!stack)
		return (1);
	return ((*stack == NULL));
}
