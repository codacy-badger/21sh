/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:12:31 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/06 01:14:23 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	line_del(t_line **line)
{
	if (!line || !*line)
		return ;
	ft_memdel((void *)&(*line)->str);
	ft_memdel((void *)line);
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
