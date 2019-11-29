/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_curs_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 00:46:27 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		move_curs_left(t_term *term, t_input *input)
{
	ssize_t	csize;
	t_line	*line;

	line = input->line;
	if (line->i > 0)
	{
		csize = getcsize_rev(&line->str[line->i - 1], line->i - 1);
		line->i -= csize;
		movcleft(term);
	}
	return (0);
}
