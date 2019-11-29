/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_del_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 01:44:22 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		line_del_char(t_line *line)
{
	char	*str;
	size_t	csize;

	if (!line || !(str = line->str))
		return (-1);
	csize = getcsize(str[line->i]);
	ft_strremove(&str[line->i], csize);
	line->len -= csize;
	return (0);
}
