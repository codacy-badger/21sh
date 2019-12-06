/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:12:31 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/06 01:14:23 by fratajcz         ###   ########.fr       */
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

void	line_delone(t_line **line)
{
	t_line	*tmp;

	if (!line || !(*line))
		return ;
	tmp = (*line)->next;
	if ((*line)->prev)
		(*line)->prev->next = (*line)->next;
	if ((*line)->next)
		(*line)->next->prev = (*line)->prev;
	ft_memdel((void *)&(*line)->str);
	ft_memdel((void *)line);
	(*line) = tmp;
}

void	line_del(t_line **line)
{
	if (!line || !*line)
		return ;
	while ((*line)->prev)
		(*line) = (*line)->prev;
	while (*line)
		line_delone(line);
}

t_line	*line_new(size_t size)
{
	t_line	*line;

	if (!(line = (t_line *)ft_memalloc(sizeof(*line))))
		return (NULL);
	if (size > 0 && !(line->str = (char *)ft_memalloc(size)))
	{
		ft_memdel((void *)&line);
		return (NULL);
	}
	line->size = size;
	return (line);
}
