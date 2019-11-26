/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 01:44:22 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	line_add(t_line **head, t_line *line)
{
	t_line	*tmp;

	if (!head)
		return ;
	if (!*head)
		*head = line;
	else
	{
		if ((*head)->next)
			(*head)->next->prev = line;
		tmp = (*head)->next;
		(*head)->next = line;
		line->next = tmp;
		line->prev = *head;
	}
}
