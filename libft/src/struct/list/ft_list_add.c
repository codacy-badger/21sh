/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 17:11:09 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/29 00:15:24 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

/*
** add a new entry after the specified list head
*/

void	ft_list_add(void *data, t_list_head *head)
{
	t_list_head *new;

	if ((new = ft_list_new_head(data)) == NULL)
		return ;
	new->next = head->next;
	head->next->prev = new;
	new->prev = head;
	head->next = new;
}
