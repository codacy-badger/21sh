/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 19:30:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 16:38:29 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_line	*line_add(t_line **head, t_line *line, int stack)
{
	t_line	*curr;

	if (!head || !line)
		return (NULL);
	if (!(*head))
		return ((*head) = line);
	if (stack)
	{
		line->next = (*head);
		line->prev = (*head)->prev;
		if (line->prev)
			line->prev->next = line;
		(*head)->prev = line;
		return ((*head) = line);
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = line;
	line->prev = curr;
	return (line);
}
