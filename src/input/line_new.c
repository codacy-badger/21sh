/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 01:44:22 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_line	*line_new(size_t size)
{
	t_line	*line;

	if (!(line = (t_line *)ft_memalloc(sizeof(*line))))
		return (NULL);
	if (!(line->str = (char *)ft_memalloc(size)))
	{
		ft_memdel((void *)&line);
		return (NULL);
	}
	line->size = size;
	return (line);
}
