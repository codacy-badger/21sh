/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_add_at.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 19:30:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 16:38:29 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_line	*line_add_at(t_line **head, t_line *line, int stack)
{
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
	line->prev = (*head);
	line->next = (*head)->next;
	if (line->next)
		line->next->prev = line;
	(*head)->next = line;
	return (line);
}
