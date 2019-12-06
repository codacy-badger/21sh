/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 17:11:09 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/29 00:15:24 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void    ft_list_foreach(t_list_head *head, void (*f)(void *a, void *priv),
		void *priv)
{
	t_list_head			*cur;

	cur = head;
	while (!ft_list_is_last(cur, head))
	{
		f(cur->data, priv);
		cur = cur->next;
	}
	f(cur->data, priv);
}