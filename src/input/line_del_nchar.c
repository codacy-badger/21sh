/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_del_nchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 01:44:22 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		line_del_nchar(t_line *line, int n)
{
	char	*str;

	if (!line || !(str = line->str))
		return (-1);
	ft_strremove(&str[line->i], n);
	line->len -= n;
	return (n);
}
