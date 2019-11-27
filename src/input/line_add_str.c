/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_add_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 01:44:22 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		line_add_str(t_line *line, char *s)
{
	char	*str;
	size_t	olds;
	size_t	news;
	size_t	len;

	if (!line || !(str = line->str))
		return (-1);
	len = ft_strlen(s);
	while (line->len + len > line->size - 1)
	{
		olds = line->len;
		news = line->size * 2;
		if (!(line->str = (char *)ft_memrealloc(str, olds, news)))
			return (-1);
		line->size = news;
	}
	ft_strinsert(&line->str[line->i], s, len);
	line->len += len;
	return (0);
}
