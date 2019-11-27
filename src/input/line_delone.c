/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_delone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 01:44:22 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
