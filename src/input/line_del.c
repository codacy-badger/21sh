/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 01:44:22 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	line_del(t_line **line)
{
	if (!line || !*line)
		return ;
	while ((*line)->prev)
		(*line) = (*line)->prev;
	while (*line)
		line_delone(line);
}
